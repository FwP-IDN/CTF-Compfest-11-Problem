/*! \fn dividePolynomialByPolynomial
*   \brief Try to make a division
*   
*   \param iNumerator( vector< long long >& ) The dividend ; updated if the remainder is 0
*   \param iDenominator( const vector< long long > ) The divisor
*   \return bool: True if iNumerator is divisible by iDenominator. In this case, iNumerator is updated to the quotient
*/
#include<bits/stdc++.h>
using namespace std;

vector<long long> dividePolynomialByPolynomial( vector< long long >& iNumerator, const vector< long long >& iDenominator )
{
    unsigned int dN( iNumerator.size( ) - 1 ), dD( iDenominator.size( ) - 1 );
     
    vector< long long > iWorking( iNumerator ), iQuotient;
     
    unsigned int i;
    long long iTemp;
     
    while( dN >= dD ){
        iTemp = iWorking[ dN ] / iDenominator[ dD ];
        iQuotient.insert( iQuotient.begin( ), iTemp );
         
        for( i = 0; i <= dD; i++ ) 
		    iWorking[dN - i] -= iTemp * iDenominator[dD - i];    
		dN--;               
		while( iWorking[ dN ] == 0 && dN >= 1 && dN >= dD ){
            iQuotient.insert( iQuotient.begin( ), 0 );
            dN--;
        }
    }
    for( i = 0; i <= dN; i++ )
    {
        if( iWorking[i] != 0 )
            cout<<"SALAH\n";
    }     
    return iQuotient;
}

int main(){
	freopen("magic_numbers.txt", "r", stdin);
	freopen("hasil.txt", "w", stdout);
	const int deg = 100000;
	vector<long long> A,N,B;
	for(int i=0; i<=deg; i++){
		long long tmp;
		cin>>tmp;
		A.push_back(tmp);
	}
	for(int i=0; i<=deg*2; i++){
		long long tmp;
		cin>>tmp;
		N.push_back(tmp);
	}
	B=dividePolynomialByPolynomial(N, A);
	for(int i=0; i<B.size(); i++){
		cout<<B[i]<<' ';
	}
	cout<<'\n';
	fclose(stdout);
	fclose(stdin);
	return 0;
}