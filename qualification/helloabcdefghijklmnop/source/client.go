

package main

import (
	"fmt"
	"time"
	"net"
	"os"
	"bufio"
)

func main() {
	var name string
	fmt.Printf("Please enter your name:	")
	fmt.Scan(&name)

	server := "104.250.105.109:19007"

	conn, err := net.Dial("tcp", server)

	if err != nil{
		fmt.Println("Oops, something went terribly wrong!")
		os.Exit(0)
	}

	fmt.Println("Please wait...")
	time.Sleep(1 * time.Second)

	fmt.Printf("Welcome %s to Best And Turbo Messaging Anyone aNywhere!\n", name)
	fmt.Printf("BATMAN version 0.5\n")
	fmt.Printf("Messaging is currently down, however the server should still be up\n")
	var choice string
	for true	{
		fmt.Printf("1: Test server\n2: Exit\nYour Choice: ")
		fmt.Scan(&choice)

		if choice == "1"	{
			fmt.Println("What would you like to send to the server?")

			scanner := bufio.NewScanner(os.Stdin)
			scanner.Scan()
			message := scanner.Text()

			to_send := string(uint16(len([]rune(message)))) + message

			fmt.Printf("Sent: %s\n", message)
			conn.Write([]byte(to_send + "\n"))

			recieved, err := bufio.NewReader(conn).ReadString('\n')
			recieved = recieved[:uint16(len([]rune(recieved)))-1]

			if err != nil{
				fmt.Println("Oops, something went terribly wrong!")
				os.Exit(0)
			}

			fmt.Printf("Server sent back: %s\n", recieved)

			if recieved == message	{
				fmt.Println("Yup server is still good!")
			} else {
				fmt.Println("Oh no the server has gone bad!")	
			}
			
		} else if choice == "2"	{
			fmt.Println("Bye bye, thanks for using our service!")
			conn.Close()
			os.Exit(0)
		} else {
			fmt.Println("Invlid choice")
		}
	}

}