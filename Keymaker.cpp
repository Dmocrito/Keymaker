//╔══════════════════════════════════════════════════════════╗
//║                          KEYMAKER                        ║
//╠══════════════════════════════════════════════════════════╣
//║   The KEYMAKER is a program that creates shortcuts       ║
//║ commands that can be used by other programs to gain      ║
//║ quick access to various areas within the Internet.       ║
//╟──────────────────────────────────────────────────────────╢
//║                                                  -mMm-   ║
//╚══════════════════════════════════════════════════════════╝
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <cstdio>

using namespace std;

//─── Functions ──────────────────────────────────────────────
string Sum(string A, string B);
string Minus(string A, string B);
string SigVal(string A);
string iterDiv(string A, string B, string& R);
string fastDiv(string A, string B, string& R);
string GenKey(string Lock, string Pass);
void Translate(string& A);
bool Equal(string A, string B);
bool GrtEq(string A, string B);
bool Grt(string A, string B);
string Verbum(void);
//────────────────────────────────────────────────────────────

//═════ MAIN ═════════════════════════════════════════════════
int main(int narg, char *argc[]){

	// Variables
	int i,opt;
	string sopt;
	int cnt;
	string var,pass,dict;
	string Lock,Key;

	ifstream file;


	// Check the input variables

	if(narg>1) //No menu
	{
		// Read Lock
		Lock = argc[1];

		if(narg==2) // Load the Master-key
		{
			// Import Master-key
			file.open("Master-key");

			getline(file,pass);

			file.close();
		}
		else       // User-defined master-key
		{
			pass = argc[2];
		}

		//=== Generate the Key ===
		Key = GenKey(Lock,pass);

		// Check if we need to show the key
		if(narg==3 && string(argc[3])=="-showKey")
		{
			// Return the Key
			cout<<"═══ Key ════════════════"<<endl;
			cout<<Key<<endl;
			cout<<"════════════════════════"<<endl;
		}
		else
		{
			// Copy the string to the clipboard using xclip
			string command = "echo '" + std::string(Key) + "' | xclip -selection clipboard";
    		system(command.c_str());
			
			cout<<"═══ Key ════════════════"<<endl;
			cout<<" > Ready to be used"<<endl;
			cout<<"════════════════════════"<<endl;
		}
	}
	else
	{
		opt=0;
		// Main Menu
		while(opt<4)
		{
			// Clean mess
			std::system("clear");

			// Main Menu stuff
			cout<<"╔══════════════════════════════════════════════════╗"<<endl;
			cout<<"║   _     _  __         __  __      _              ║"<<endl;
			cout<<"║  ( )   | |/ /___ _  _|  \\/  |__ _| |_____ _ _    ║"<<endl;
			cout<<"║  /_\\   | ' </ -_) || | |\\/| / _` | / / -_) '_|   ║"<<endl;
			cout<<"║   =    |_|\\_\\___|\\_, |_|  |_\\__,_|_\\_\\___|_|     ║"<<endl;
			cout<<"║                  |__/                    -mMm-   ║"<<endl;
			cout<<"╠══════════════════════════════════════════════════╣"<<endl; 
			cout<<"║ [1] Generate a key from a stored MasterKey       ║"<<endl;
			cout<<"║ [2] Show stored MasterKey                        ║"<<endl;
			cout<<"║ [3] Generate a key from a specific MasterKey     ║"<<endl;
			cout<<"║                                                  ║"<<endl;
			cout<<"║ [4] Exit                                         ║"<<endl;
			cout<<"╚══════════════════════════════════════════════════╝"<<endl;

			cnt = 0;
			do 
			{
				// Proper set user-interface engaggement
				if(cnt==1 || cnt==3){
					cout<<"   - That was not even an option ¬¬"<<endl;
				}
				if(cnt==5){
					cout<<"   - You are testing me, are you?"<<endl;
				}
				if(cnt==8){
					cout<<"   - Please, stop it! TT_TT"<<endl;
				}

				// Option selection
				cout<<"   Option: ";
				cin >> sopt;

				try
				{
					opt = stoi(sopt);
				}
				catch (std::invalid_argument const &e)
				{
					cout<<"   - Invalid option -"<<endl;
					opt = 0;
				}


				cnt++;

			}while(opt>4 || opt<1);


			if(opt==1) // Generate a key from a stored MasterKey
			{
				cout<<"   ═════════════════════════════════════════════"<<endl;
				cout<<"       [1] Generate Key from stored MasterKey   "<<endl;
				cout<<"   ═════════════════════════════════════════════"<<endl;
				cout<<"     - Reading MasterKey -------------";

				// Import Master-key
				file.open("Master-key");

				getline(file,pass);

				file.close();

				cout<<" [Ok]"<<endl;

				// Ask for the Lock
				cout<<"     - Introduce Lock: ";

				cin >> Lock;

				//=== Generate the Key ===
				Key = GenKey(Lock,pass);

				// Return the Key
				cout<<"\n   ═══ Key ════════════════"<<endl;
				cout<<"   "<<Key<<endl;
				cout<<"   ════════════════════════\n"<<endl;	
			}
			if(opt==2) // SHOW ME WHAT YOU GOT
			{
				cout<<"   ═════════════════════════════════════════════"<<endl;
				cout<<"       [2] Stored MasterKey                     "<<endl;
				cout<<"   ═════════════════════════════════════════════"<<endl;

				// Import Master-key
				file.open("Master-key");

				getline(file,pass);

				file.close();

				cout<<endl<<"   MasterKey:"<< pass <<endl<<endl;
			}
			if(opt==3) // // Generate a key given the Lock and the masterkey
			{	
				cout<<"   ═════════════════════════════════════════════"<<endl;
				cout<<"       [3] Generate Key with your own MasterKey "<<endl;
				cout<<"   ═════════════════════════════════════════════"<<endl;

				// Ask for the Lock
				cout<<"     - Introduce Lock: ";
				cin >> Lock;

				// Ask for the MasterKey
				cout<<"     - Introduce MasterKey: ";
				cin >> pass;

				//=== Generate the Key ===
				Key = GenKey(Lock,pass);

				// Return the Key
				cout<<"\n   ═══ Key ════════════════"<<endl;
				cout<<"   "<<Key<<endl;
				cout<<"   ════════════════════════\n"<<endl;		
			}

			if(opt!=4) // Wait for more
			{
				system("read -p 'Press Enter to continue...' var");
			}
		}			
	}

	return 0;
}

//════════════════════════════════════════════════════════════

/************************************************************/
/*     Function: GenKey                                     */
/* The core of the Keymaker: this function relies on the    */
/* overwellming numberical complexity of the division       */
/* to generate a robust functional Key.                     */
/************************************************************/
string GenKey(string Lock, string Pass)
{
	// Variables
	int N,ksize;
	string Key,R;

	// Check characters
	Translate(Lock);
	Translate(Pass);

//--- Default size of the key ---
	ksize = 21;
//-------------------------------

	if(GrtEq(Lock,Pass))
	{
		Key = fastDiv(Lock,Pass,R);
	}
	else // The size is not important...
	{
		Key = fastDiv(Pass,Lock,R);
	}

	// Analyize the final size of the Key
	N = Key.length();

	while(N<ksize) // If the key is too short
	{
		Key = Key+Key;
		N = Key.length();
	}

	// Retun the key with the fixed size
	return Key.substr(0,ksize);
}


/************************************************************/
/*     Function: fastDiv                                    */
/* This function divides A by B using the traditional way   */
/************************************************************/
string fastDiv(string A, string B, string& R)
{
	int i,cnt;
	int NA,NP;
	bool sig;
	string aux,C,P,Q,Qt;

	// Determine length of each string
	NA = A.length();

	// Perofrm division in the standard way
	if(Grt(B,A)){
		Qt = "0";
	}
	else{
		// Initialization
		i = 0;
		C = "";
		P = "";

		for(i=0;i<NA;i++)
		{
			if(GrtEq(B,C)){
				C = C + A[i];
			}
			else{
				P = P + A[i];
			}
		}

		// Partial division
		Q = iterDiv(C,B,R);

		// Update P
		if(!Equal(R,"0"))
		{	
			P = R + P;
		}

		// Check residuals
		NP = P.length();

		i   = 0;
		cnt = 0;
		sig = false;

		while(!sig && i<NP)
		{
			aux = P[i];

			if(Equal(aux,"0"))
			{
				Q = Q + "0";

				cnt++;

				if(i+1<NP)
				{
					aux = P[i+1];
					if(Equal(aux,"0")){
						i++;
					}
					else{
						sig = true;
					}
				}
				else
				{
					sig = true;
				}
			}
			else
			{
				sig = true;
			}
		}
		// Clean P
		if(cnt>0)
		{
			P.erase(0,cnt);
		}

		//cout << C + "  " + R + "|" + P + " ---- " + Q << endl;

		// Check if more divisions are necessary
		if(Grt(B,P))
		{
			Qt = Q;
		}
		else
		{
			Qt = Q + fastDiv(P,B,R);
		}
	}

	return Qt;
}
/************************************************************/
/*     Function: iterDiv                                    */
/* This function divides A between B                        */
/*                                                          */
/*   Note: It becomes extremly inneficient when A >>> B, for*/
/*         that case use nrmDiv instead                     */           
/************************************************************/
string iterDiv(string A, string B, string& R)
{
	int i;
		string Qt,aux;

	//=== Division ===
	if(Grt(B,A))
	{
		Qt = "0";
	}
	else // Iterative division
	{
		Qt  = "0";
		aux = B;

		while(GrtEq(A,aux))
		{
			aux = Sum(aux,B);
			Qt  = Sum(Qt,"1");
		}
	}

	// Rest
	R = Minus(A,Minus(aux,B));

	return Qt;
}

/************************************************************/
/*     Function: Minus                                      */
/* Subntract the value of the minor string to the biggest   */
/************************************************************/
string Minus(string A, string B)
{
	int i,n,aux;
	int NA,NB,N,vA,vB,vC;
	bool llvo;
	string Dict,Aux,sA,sB,C;

	// Load Dictionary
	Dict = Verbum();

	// Determine length
	NA = A.length();
	NB = B.length();

	//=== Minus ===
	if(Equal(A,B)) // That was easy
	{
		C = "0";
	}
	else if(Grt(B,A))
	{
		C = Minus(B,A);
	}
	else
	{
		// Initialization
		C = "";
		llvo = false;

		// Main loop
		for(i=1;i<=NA;i++)
		{
			// Initialice
			vA = Dict.find(A[NA-i]);
			vB = 0;
			vC = 0;

			if(i<=NB)
			{
				vB = Dict.find(B[NB-i]);
			}

			//llvo?
			if(llvo)
			{
				vB = vB + 1;
			}

			// Check size
			if(vB>vA)
			{
				vA = vA + 63;

				llvo = true;
			}
			else
			{
				llvo = false;
			}

			// Subtraction //
			vC = vA - vB;

			// Translate back (always it's < 63 if everything goes right);
			C = Dict[vC] + C;
		}
	}

	return SigVal(C);
}

/************************************************************/
/*     Function: Sum                                        */
/* Add the value of two string as a string                  */
/************************************************************/
string Sum(string A, string B)
{
	int i,n,aux;
	int NA,NB,N,vA,vB,vC;
	bool llvo;
	string Dict,Aux,sA,sB,C;

	// Load Dictionary
	Dict = Verbum();

	// Determine length of each string
	NA = A.length();
	NB = B.length();

	// Find the maximum
	if(NB>NA){
		N = NB;
	}
	else{
		N = NA;
	}

	// Initialize
	C = "";
	llvo = false;

	for(i=1;i<=N;i++)
	{
		// Initialize
		vA = 0;
		vB = 0;
		vC = 0;

		// Translate values
		if(i<=NA){
			vA = Dict.find(A[NA-i]);
		}

		if(i<=NB){
			vB = Dict.find(B[NB-i]);
		}

		// Sum //
		vC = vA + vB;

		// llvo?
		if(llvo){
			vC = vC+1;
		}

		// Translate back
		if(vC<63)
		{
			C = Dict[vC] + C;

			llvo = false;
		}
		else
		{
			n = vC%63;
			C = Dict[n] + C;

			llvo = true;
		}
	}

	// Check final value
	if(llvo){
		C = "1"+C;
	}

	return C;
}

/************************************************************/
/*     Function: SigVal                                     */
/* This function remove meaningless zeros in the let given  */
/* a string, leaving only the significant values.           */
/************************************************************/
string SigVal(string A)
{
	int i,N;
	bool imp;
	string aux,C;

	// Initialization
	N   = A.length();
	imp = false;
	C   = "";

	// Clean loop
	i = 0;
	while(!imp && i<N-1)
	{
		aux = A[i];
		if(!Equal(aux,"0"))
		{
			imp = true;
		}
		else
		{
			i++;
		}
	}

	// Sotre significant values
	while(i<N)
	{
		C = C + A[i];
		i++;
	}

	return C;
}

/************************************************************/
/*     Function: Prod                                       */
/* Determines the product of A times B                      */
/************************************************************/
string Prod(string A, string B)
{
	string cnt,C{""};

	// Determine the bigger string
	if(GrtEq(A,B))
	{
		//=== Iterative product ===
		C   = "0";
		cnt = "1";

		while(GrtEq(B,cnt))
		{
			C   = Sum(A,C);
			cnt = Sum(cnt,"1");
		}
	}
	else // Long live the asociative property!!!
	{
		C = Prod(B,A);
	}

	return C;

}

/************************************************************/
/*     Function: GrtEq                                      */
/* This funtcion determines if A is greater or equal than B */
/************************************************************/
bool GrtEq(string A, string B)
{
	// Let assume...
	bool gr {false};

	// Check first B is smaller than A
	if(!Grt(B,A))
	{
		gr = true;
	}

	return gr;
}

/************************************************************/
/*     Function: Grt                                        */
/* This funtcion determines if A is greater than B          */
/************************************************************/
bool Grt(string A, string B)
{
	int i;
	int NA,NB,vA,vB;
	bool gr;
	string Dict;

	// Load Dictionary
	Dict = Verbum();

	// Determine lengths
	NA = A.length();
	NB = B.length();

	//--- Check sizes ---
	if(NA > NB)
	{
		gr = true;
	}
	else if(NA==NB)
	{
		// Compare element by element
		vA = Dict.find(A[0]);
		vB = Dict.find(B[0]);

		if(vA>vB)
		{
			gr = true;
		}
		else if(vA<vB)
		{
			gr = false;
		}
		else
		{
			if(NA>1)
			{
				A.erase(A.begin());
				B.erase(B.begin());

				gr = Grt(A,B);
			}
			else
			{
				gr = false;
			}
		}
	}
	else
	{
		gr = false;
	}

	return gr;
}

/************************************************************/
/*     Function: Equal                                      */
/* This funtcion determines if A and B are equal            */
/************************************************************/
bool Equal(string A, string B)
{
	int i;
	int NA,NB,vA,vB;
	bool eq;
	string Dict;

	// Load Dictionary
	Dict = Verbum();

	// Determine lengths
	NA = A.length();
	NB = B.length();

	//--- Check if their equal---
	if(NA==NB)
	{
		// Comapre element by element
		eq = true;
		i  = 0;

		while(eq && (i<NA))
		{
			// Take elements
			vA = Dict.find(A[i]);
			vB = Dict.find(B[i]);

			// Check the values
			if(vA!=vB){
				eq = false;
			}

			i++;
		}
	}
	else
	{
		eq = false;
	}

	return eq;
}


/************************************************************/
/*     Function: Translate                                  */
/*   This function checks that only allowed characters were */
/* used in the string. Any other extra character is         */
/* replaced by "_"                                          */
/************************************************************/
void Translate(string& A)
{
	int i,N,cnt;
	bool find;
	string Dict;

	// Determine the length of the string
	N = A.length();

	// Read the general ledger
	Dict = Verbum();

	// Check allowed characters
	for(i=0;i<N;i++)
	{
		find = false;
		cnt  = 0;

		while(!find && cnt<62)
		{
			if(A[i]==Dict[cnt]){
				find = true;
			}
			else{
				cnt ++;
			}
		}

		// Update character
		A[i] = Dict[cnt];
	}

	return;
}

/************************************************************/
/*     Function: Verbum                                     */
/* General ledge string for the keys                        */
/************************************************************/
string Verbum(void)
{
	return "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVXYZ$_";
}