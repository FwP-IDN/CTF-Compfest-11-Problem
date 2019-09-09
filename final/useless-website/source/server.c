#include <arpa/inet.h>
#include <ctype.h>
#include <microhttpd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PORT 8000
const char *user_default = "root";
const char *password_default = ">`@Yal(X.1}gcom8{rvy@p'~&T@b}Vx'b|Lg?'iu%@CV!fzCqH";
const int g_max_size = 256;

struct postStatus
{
    int status;
    char *buff;
};

char *replace(char *str, char find, char replace)
{
    char *current_pos = strchr(str, find);
    while (current_pos)
    {
        *current_pos = replace;
        current_pos = strchr(current_pos + 1, find);
    }
    return str;
}

char *decode(const char *s)
{
    char *dec = malloc(strlen(s) + 1);
    char *o;
    const char *end = s + strlen(s);
    int c;

    for (o = dec; s <= end; o++)
    {
        c = *s++;
        if (c == '+')
            c = ' ';
        else if (c == '%' && (!isxdigit(*s++) ||
                              !isxdigit(*s++) ||
                              !sscanf(s - 2, "%2x", &c)))
            return "404";

        if (dec)
            *o = c;
    }

    return dec;
}

char *cat(const char *file_name)
{
    char *buffer;
    long length;
    FILE *f = fopen(file_name, "r");

    if (f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length + 1);
        buffer[length] = 0;
        fread(buffer, 1, length, f);
        fclose(f);
        return buffer;
    }
    return cat("/var/www/html/404.html");
}

char *neo_cat(const char *command)
{
    char file_name[g_max_size];
    snprintf(file_name, g_max_size, "/tmp/%d", rand() % (1000000 - 100000) + 100000);

    char *d_command = decode(command);
    d_command = replace(d_command, 'a', 'a');
    d_command = replace(d_command, 'k', 'k');
    d_command = replace(d_command, 'u', 'u');
    d_command = replace(d_command, 'g', 'g');
    d_command = replace(d_command, 'a', 'a');
    d_command = replace(d_command, 'n', 'n');
    d_command = replace(d_command, 't', 't');
    d_command = replace(d_command, 'e', 'e');
    d_command = replace(d_command, 'n', 'n');
    d_command = replace(d_command, 'g', 'g');
    d_command = replace(d_command, '\'', '+');
    d_command = replace(d_command, '\"', '+');
    d_command = replace(d_command, '#', '+');
    d_command = replace(d_command, '*', '+');
    d_command = replace(d_command, '(', '+');
    d_command = replace(d_command, ')', '+');
    d_command = replace(d_command, '<', '+');
    d_command = replace(d_command, '>', '+');
    d_command = replace(d_command, '`', '+');
    d_command = replace(d_command, '~', '+');
    d_command = replace(d_command, '-', '-');
    d_command = replace(d_command, '+', '+');

    char cmd[g_max_size];
    snprintf(cmd, g_max_size, "timeout 2 %s > %s", d_command, file_name);
    system(cmd);
    free(d_command);

    char *output = cat(file_name);
    snprintf(cmd, g_max_size, "rm %s", file_name);
    system(cmd);

    return output;
}

char *parse(char *input, const char *find)
{
    char *found = strstr(input, find);
    if (!found)
    {
        return "404";
    }
    char *assign = found + strlen(find);
    if (*assign != '=')
    {
        return "404";
    }
    char *value = assign + 1;
    char *end_value = strchr(value, '&');
    if (!end_value)
        end_value = strchr(value, 0);
    int length = end_value - value;

    value[length] = 0;
    return value;
}

int send_page(struct MHD_Connection *connection, char *page, int status_code)
{
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void *)page, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, status_code, response);
    MHD_destroy_response(response);
    return ret;
}

int do_403(struct MHD_Connection *connection)
{
    char *page = cat("/var/www/html/403.html");
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void *)page, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_FORBIDDEN, response);
    MHD_destroy_response(response);
    return ret;
}

int commander(struct MHD_Connection *connection, char *input_str)
{
    char *command = parse(input_str, "command");
    if (strcmp(command, "404"))
        return send_page(connection, neo_cat(command), MHD_HTTP_OK);
    return send_page(connection, "Enter your command.", MHD_HTTP_OK);
}

static int answer_to_connection(
    void *cls, struct MHD_Connection *connection,
    const char *url, const char *method,
    const char *version, const char *upload_data,
    size_t *upload_data_size, void **con_cls)
{
    srand(time(0) + clock());
    char input_str[g_max_size];
    input_str[g_max_size - 1] = 0;

    struct sockaddr_in *so = (struct sockaddr_in *)MHD_get_connection_info(connection, MHD_CONNECTION_INFO_CLIENT_ADDRESS)->client_addr;
    char *ip_address = inet_ntoa(so->sin_addr);

    if (0 == strcmp(method, "POST"))
    {
        struct postStatus *post = NULL;
        post = (struct postStatus *)*con_cls;

        if (post == NULL)
        {
            post = malloc(sizeof(struct postStatus));
            post->status = 0;
            *con_cls = post;
        }

        if (!post->status)
        {
            post->status = 1;
            return MHD_YES;
        }
        else
        {
            if (*upload_data_size != 0)
            {
                post->buff = malloc(*upload_data_size + 1);
                snprintf(post->buff, *upload_data_size + 1, "%s", upload_data);
                *upload_data_size = 0;
                return MHD_YES;
            }
            else
            {
                strncpy(input_str, post->buff, g_max_size);
                free(post->buff);
            }
        }

        if (post != NULL)
            free(post);
    }
    puts(input_str);

    if (0 == strcmp(url, "/"))
    {
        return send_page(connection, cat("/var/www/html/index.html"), MHD_HTTP_OK);
    }

    if (0 == strcmp(url, "/admin"))
    {
        char *password_in;
        char *user_in = MHD_basic_auth_get_username_password(connection, &password_in);

        int fail = ((user_in == NULL) ||
                    strncmp(password_default, password_in, strlen(password_in)));

        if (!fail  || 0 == strcmp(ip_address, "127.0.0.1"))
        {
            return commander(connection, input_str);
        }
        else
        {
            return do_403(connection);
        }
    }

    else if (0 == strcmp(url, "/debug"))
    {
        int debug_v = 0;
        printf(input_str, &debug_v);
        // printf("%d\n", debug_v);
        if (debug_v == 1337 || 0 == strcmp(ip_address, "127.0.0.1"))
        {
            return commander(connection, input_str);
        }
        else
        {
            return do_403(connection);
        }
    }

    else if (0 == strcmp(url, "/internal"))
    {
        if (0 == strcmp(ip_address, "127.0.0.1"))
        {
            return commander(connection, input_str);
        }
        else
        {
            return do_403(connection);
        }
    }

    else if (0 == strcmp(url, "/service"))
    {
        char *type = parse(input_str, "type");
        char *variant = parse(input_str, "variant");
        char *query = parse(input_str, "query");
        char *service = parse(input_str, "service");
        char command[g_max_size];

        if (0 == strcmp(service, "cowsay"))
        {
            if (strcmp(variant, "404"))
            {
                if (0 == strcmp(type, "cowsay"))
                    snprintf(command, g_max_size, "cowsay -f %s %s", variant, query);
                else if (0 == strcmp(type, "cowthink"))
                    snprintf(command, g_max_size, "cowthink -f %s %s", variant, query);
                return send_page(connection, neo_cat(command), MHD_HTTP_OK);
            }
        }
        else if (0 == strcmp(service, "factor"))
        {
            snprintf(command, g_max_size, "factor 1 %s", query);
            return send_page(connection, neo_cat(command), MHD_HTTP_OK);
        }
        else if (0 == strcmp(service, "figlet"))
        {
            snprintf(command, g_max_size, "figlet %s", query);
            return send_page(connection, neo_cat(command), MHD_HTTP_OK);
        }
        else if (0 == strcmp(service, "fortune"))
        {
            if (strcmp(variant, "404"))
            {
                snprintf(command, g_max_size, "fortune %s", variant);
                return send_page(connection, neo_cat(command), MHD_HTTP_OK);
            }
        }
        else if (0 == strcmp(service, "moo"))
        {
            if (0 == strcmp(variant, "1"))
            {
                snprintf(command, g_max_size, "apt-get moo");
                return send_page(connection, neo_cat(command), MHD_HTTP_OK);
            }
            else if (0 == strcmp(variant, "2"))
            {
                snprintf(command, g_max_size, "apt-get moo moo");
                return send_page(connection, neo_cat(command), MHD_HTTP_OK);
            }
            else if (0 == strcmp(variant, "3"))
            {
                snprintf(command, g_max_size, "apt-get moo moo moo");
                return send_page(connection, neo_cat(command), MHD_HTTP_OK);
            }
        }
        else if (0 == strcmp(service, "pi"))
        {
            snprintf(command, g_max_size, "pi %s", query);
            return send_page(connection, neo_cat(command), MHD_HTTP_OK);
        }
        else if (0 == strcmp(service, "rev"))
        {
            snprintf(command, g_max_size, "echo %s | rev", query);
            return send_page(connection, neo_cat(command), MHD_HTTP_OK);
        }
        else if (0 == strcmp(service, "whois"))
        {
            snprintf(command, g_max_size, "whois %s", query);
            return send_page(connection, neo_cat(command), MHD_HTTP_OK);
        }
        return do_403(connection);
    }

    else if (0 == strcmp(url, "/robots.txt"))
    {
        return send_page(connection, cat("/var/www/html/robots.txt"), MHD_HTTP_OK);
    }

    else if (0 == strcmp(url, "/personal-stuff"))
    {
        return send_page(connection, "YTFmYTY1YmJlZDM1ODA3MDYyYWIyMmE5Zjk2ZDNiY2Y", MHD_HTTP_OK);
    }

    else
    {
        return send_page(connection, cat("/var/www/html/404.html"), MHD_HTTP_NOT_FOUND);
    }
}

int main(int argc, char *argv[])
{
    printf("Running server on port %d.", PORT);
    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, &answer_to_connection, NULL, MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    pause();
    MHD_stop_daemon(daemon);
    return 0;
}
