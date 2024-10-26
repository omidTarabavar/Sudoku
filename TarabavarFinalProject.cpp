#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/*
			Hi :)
Omid tarabavar - Final project
tozihat har function dar ghesmat tarif function neveshte shode
*/
const int Max =9;
const int cols =(2*Max)-1;

void storeInput(int p[][Max],int rows,string inP);
int charToInt(char a);
int stringLenght(string a);
void adFixer(string& ad);
void arrayCleaner(int arr[][Max],int Size);
void puzzleSaver(int Puz[][Max],int r,string adRess);
void copyOfArray(int ar1[][Max],int rowAr1,int ar2[][Max],int rowAr2);
void loadPuzzleFunc(int lPuz[][Max],int rowS,string lAdress);
void showPuzzle(int sPuz[][Max],int sRow,int copyPuz[][Max],int copyRows);
void fillPuz(int fPuz[][Max],int fRow,int copyPuz[][Max],int copyRow,string ans);
bool isFillPuz(int iFPuz[][Max],int iFRow);
bool puzzleChecker(int chPuz[][Max],int chRow,int ErrorAr[],int size);
bool rowChecker(int a,int rchPuz[][Max],int rchRow,int rErrorAr[],int sizeEA);
bool colChecker(int b,int cchPuz[][Max],int cchRow,int cErrorAr[],int sizeEa);
bool squareChecker(int c,int sCPuz[][Max],int PuzRow);
void singleDimensionalArrayCleaner(int arr[],int size);
void showError(int eArray[],int row);
bool aOChecker(int a,int aOCPuz[][Max],int aOCRow,int oRow,int oCol);
void availableOptions(int aOPuz[][Max],int aORow,int aArray[][12],int size);
void singleOptionSolver(int sOSPuz[][Max],int sOSRow,int aOptions[][12],int aOpRow);
void arrayCleaner2(int arr[][12],int size);
void singleRowOptionChecker(int sROPuz[][Max],int rowPuz,int sROptions[][12],int sRORow);
void singleColOptionChecker(int sCOPuz[][Max],int RowPuz,int sCOptions[][12],int sCORow);
void findIndexCol(int optionArray[][12],int row,int IndexArray[],int size,int numOfCol,int& NumberOfIndexes);
int arrayLen(int ar[],int size);
int twoDemArrayLen(int ar[][12],int row);
void findIndexRow(int optionArray[][12],int row,int numOfRow,int& startingIndex,int& endingIndex);
void adressSolvedPuzzle(string& adress);
int main()
{
	// ======================================= Starting Menu =======================================
	char ans;
	bool finish = false;
	do
	{
		cout <<"1- Create Puzzle"<<endl;
		cout <<"2- Solve Puzzle"<<endl;
		cout <<"3- Auto Puzzle Solver"<<endl; // hal khodkar sodoko ro be onvan yek item be menu ezafe kardm 
		cout <<"4- Exit"<<endl<<endl;
		cout <<"-> ";
		cin >> ans; // ans = (answer) pasokh user 
		switch(ans) 
		{
		// ======================================= Create Puzzle =======================================
			case '1':
				{
					int Puzzle[Max][Max],copyPuz[Max][Max]; // puzzle 9*9 ( max = 9 )
					arrayCleaner(Puzzle,Max); // baraye 0 kardn khone haye jadval (faghat araye haye 2 bodi va tedad col:Max)
					arrayCleaner(copyPuz,Max);
					string answer,adress;
					cout << "Format input : row-col-value"<<endl;
					cout << "Input your puzzle (Done or done for stop): "<<endl;
					while(1) 
					{
						cout << "-> ";
						cin >> answer;
						bool DoneChecker= (answer == "Done" || answer == "done"); // Done ya done keyword khoroji 
						
						if(DoneChecker)
						break;
						
						else
						storeInput(Puzzle,Max,answer); // baraye zakhire input dar araye Puzzle 
						showPuzzle(Puzzle,Max,copyPuz,Max);
					}
					cout <<"Enter a file path to store your puzzle(e.g: C:\\x.txt): "; 
					cin >> adress; // string adress vared shode tavasot karbar
					adFixer(adress); // baraye dorost kardn adress ( dar khode func behtar tozih dade shode )
					puzzleSaver(Puzzle,Max,adress); // baraye zakhire arraye puzzle dar file
					break;
				}
		// ======================================= Solve Puzzle =======================================
			case '2':
				{
					int ErrorArray[100]; // arraye baraye zakhire eshkalat jadval hal shode tavasot user
					singleDimensionalArrayCleaner(ErrorArray,100); // 0 kardn khone haye jadval ( faghat arraye tak bodi )
					int loadPuzzle[Max][Max],copyOfPuz[Max][Max]; // arraye puzzle 
					arrayCleaner(loadPuzzle,Max); // 0 kardn khone haye jadval (faghat araye haye 2 bodi va tedad col:Max)
					arrayCleaner(copyOfPuz,Max);
					string loadAdress,answeR;
					cout << "Enter your Puzzle file path(e.g: C:\\puzzle.txt): ";
					cin >> loadAdress; // string adress vared shode tavasot karbar
					adFixer(loadAdress); // baraye dorost kardn adress ( dar khode func behtar tozih dade shode )
					loadPuzzleFunc(loadPuzzle,Max,loadAdress); // load kardn puzzle karbar dar arraye loadPuzzle
					copyOfArray(loadPuzzle,Max,copyOfPuz,Max);
					showPuzzle(loadPuzzle,Max,copyOfPuz,Max); // baraye namayesh jadval be user
					cout << endl;
					cout << "Format input : row-col-value"<<endl;
					cout << "-x- are Fixed numbers, so dont try to change them or you will get an ERROR"<<endl;
					cout << "Fill the Puzzle (Done or done for stop):"<<endl<<endl; 
					while(1)
					{
						cout << "-> ";
						cin >> answeR;
						bool doneChecker = (answeR == "Done" || answeR == "done"); // Done ya done keyword khoroji 
						bool isFill = isFillPuz(loadPuzzle,Max); // check kardn kamel bodn jadval
						if(doneChecker)
						{
							if(!isFill) // dar sorati ke jadval kamel nabud peygham zir namayesh dade she
							{
								cout << "The puzzle is not complete yet!"<<endl<<endl;
								continue; 
							}
							else break;
						}
						else
						fillPuz(loadPuzzle,Max,copyOfPuz,Max,answeR); // por kardn jadval ba input haye user
						cout <<endl;
						showPuzzle(loadPuzzle,Max,copyOfPuz,Max); // baraye namayesh jadval be user
						cout << endl;
					}
					cout << endl;
					bool check=puzzleChecker(loadPuzzle,Max,ErrorArray,100); // baraye check dorosti jadval
					if(check)
					cout << "Congratulation, Puzzle is correct :)"<<endl; 
					else
					{
						cout << "Your Puzzle is not correct :("<<endl<<endl;
						cout << "Problems: "<<endl<<endl;
						showError(ErrorArray,100);	// neshon dadn moshkelat jadval
					}
					finish = true;
					break;	
				}
		// ======================================= Auto Puzzle Solver =======================================
		/* 
			Mantegh Code Neveshte shode :
			 
			1- puzzle az karbar gerefte va zakhire mishe (mesl ghesmat solve puzzle ) bad puzzle be karbar namayesh dade
			mishe 
			
			2- khone haye khali jadval tavasot function (availableOptions) shenasaii mishan va adadi ke mitone dakhel ona
			gharar begire (option) ha ro peyda mikone va dakhel arraye Options zakhire mikonim ( in adad ba tavajoh be 
			satr , soton, va square peyda misn ) ( square = moraba haye 3x3 ii ke dakhel jadval sodoko hastn va tedadeshon
			ham 9 tast ) 
			
			3- vaghti tamam option ha shenasaii shod , dar sorati ke yek khoneye khali , daraye 1 option bashe tavasot
			func ( singleOptionSolver ) peyda mishe va on option be onvan value hamon khone zakhire mishe
			
			4- gahi oghat dar yek satr , yek option dar yeki az khone haye khali satr mojod hastesh ke dar hich khoneye
			digeye satr mojod nist , on item tavasot func (singleRowOptionChecker) shenasaii mishe va be onvane value 
			on khone gharar gerefte mishe ( chera ? chon har satr niaze adade 1-9 ro dara bashan , va in option faghat
			dar hamon khone mojod hastesh pas faghat ham to hamon khone jay gah dare )
			
			5- function (singleColOptionChecker) hamon kar func (singleRowOptionChecker) ro anjam mide faghat bejaye
			peymayesh roye satr , roye soton ya column peymayesh mikone 
			
			6- bade har kodom azin marahel hal , option haye har khone jadval update mishan 
			
			7- inkar enghadr edame dade mishe ta jadval por she 
			
			**** : in ravesh tavanaii hal jadval haye sakht ro nadare :( 	
		*/		
			case '3':
				{
					int len=0; // baraye peyda kardn size arraye Options estefade khahad shod
					int PuzToSolve[Max][Max],Options[Max*Max][12]; // arraye Puzzle va arraye option haye khone haye khali
					// dalil entekhab max*max : agar hameye khone haye jadval khali bashad mishe 81 ta khone ye khali
					int copyPuz[Max][Max];
					arrayCleaner(PuzToSolve,Max); // 0 kardn khone haye jadval (faghat araye haye 2 bodi va tedad col:Max)
					arrayCleaner(copyPuz,Max); // 0 kardn khone haye jadval ( faghat araye haye 2 bodi va tedad col:Max)
					string loadPsolver,temp; // loadPsolver : adress jadval , temp : copy az loadPsolver (badan niaz mishe)
					cout << "Enter your Puzzle file path(e.g: C:\\puzzle.txt): ";
					cin >> loadPsolver;
					temp = loadPsolver;
					adFixer(loadPsolver); // baraye dorost kardn adress ( dar khode func behtar tozih dade shode )
					loadPuzzleFunc(PuzToSolve,Max,loadPsolver); // load kardn puzzle karbar dar arraye PuzToSolve
					copyOfArray(PuzToSolve,Max,copyPuz,Max);
					cout << "\nYour Puzzle: "<<endl<<endl;
					showPuzzle(PuzToSolve,Max,copyPuz,Max); // namayesh puzzle be user
					cout << endl << endl << endl;
					availableOptions(PuzToSolve,Max,Options,Max*Max); // peyda kardn option baraye khone haye khali
					// marhale hal Puzzle: 
					while(1)
					{
						if(isFillPuz(PuzToSolve,Max)) break; // check Por bodn jadval (agar por shod yani jadval hal shode)
						else
						{
							len = twoDemArrayLen(Options,Max*Max); // update tedad item haye arraye option
							singleOptionSolver(PuzToSolve,Max,Options,len); // method 3 
						}
						if(isFillPuz(PuzToSolve,Max)) break;
						else
						{
							len = twoDemArrayLen(Options,Max*Max); // update tedad item haye arraye option
							singleRowOptionChecker(PuzToSolve,Max,Options,len); // method 4
						}
						if(isFillPuz(PuzToSolve,Max)) break;
						else
						{
							len = twoDemArrayLen(Options,Max*Max); // update tedad item haye arraye option
							singleColOptionChecker(PuzToSolve,Max,Options,len); // method 5
						}
					}
				    // bad az hal jadval : 
					cout << "Solved Version: "<<endl<<endl;
					showPuzzle(PuzToSolve,Max,copyPuz,Max); // namayesh puzzle be user
					adressSolvedPuzzle(loadPsolver); // avaz kardn adress dade shode (c:\x.txt --> c:\x_solved.txt)
					adressSolvedPuzzle(temp); // temp = yek copy az loadPsolver ke inja ham ono avaz mikonim
					puzzleSaver(PuzToSolve,Max,loadPsolver); // zakhire jadval dar loadPsolver jadid
					cout << endl<<endl;
					cout <<"Your solved version saved to: "<<temp<<endl; 
					finish = true;
					break;	
				}
		// ======================================= Exit =======================================
			case '4':
				break; 
				
			default:
				{
					cout << "Enter a valid number!"<<endl;
					break;
				}
		}
		cout << endl;
	}while(ans != '4' && finish == false);
	return 0;
}
	// ======================================= Functions =======================================
void storeInput(int p[][Max],int rows,string inP)
{
	// baraye zakhire input karbar ke be shkel (row-col-value) hastesh dar araye
	int row = charToInt(inP[0])-1;
	int col = charToInt(inP[2])-1;
	int val = charToInt(inP[4]);
	p[row][col]=val;
}
int charToInt(char a)
{
	// baraye tabdil numeric char be int
	int res=static_cast<int>(a)-48;
	return res;
}
int stringLenght(string a)
{
	// baraye bedast avordn lenght string
	int res=0;
	while(a[res] != '\0')
	res ++;
	return res;
}
void arrayCleaner(int arr[][Max],int size)
{
	// baraye 0 kardn khane haye yek arraye 
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<Max;j++)
		{
			arr[i][j]=0;
		}
	}
}
void arrayCleaner2(int arr[][12],int size)
{
	// baraye 0 kardn khane haye yek arraye 
	// fargh in func ba arrayCleaner dar column arraye parametreshon hastesh 
	// in 12 taii hast va on 9taii 
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<12;j++)
		{
			arr[i][j]=0;
		}
	}
}
void adFixer(string& ad)
{
	// baraye tabdil '\' be '\\' dar adress haii ke karbar vared mikone
	// dalil : chon baraye zakhire dar fstream niaz be tabdil '\' be '\\' darim
	// ad = adress
	string copy;
	int len = stringLenght(ad);
	for(int i=0;i<len;i++)
	{
		copy += ad[i];
		if(ad[i]=='\\')
		copy += '\\';	
	}
	ad = copy;
}
void puzzleSaver(int Puz[][Max],int r,string adRess)
{
	// baraye zakhire arraye puzzle dar file texti ke karbar adressesho mide
	// r = row 
	ofstream myFile(adRess,ios::app);
	for(int i=0;i<r;i++)
	{
		for(int j=0;j<Max;j++)
		{
			if(Puz[i][j] == 0)
			{
				myFile<<"?"; // khane haye khali ba '?' namayesh dade misahn
			}
			else
			{
				myFile << Puz[i][j];
			}
			if(j != (Max-1))
			myFile<<"-";
			else
			{
				myFile << "\n";
			}
		}
	}
}
void copyOfArray(int ar1[][Max],int rowAr1,int ar2[][Max],int rowAr2)
{
	// baraye copy gereftan az yek arraye 2bodi 
	for(int i=0;i<rowAr1;i++)
	{
		for(int j=0;j<Max;j++)
		{
			ar2[i][j] = ar1[i][j];
		}
	}
}
void loadPuzzleFunc(int lPuz[][Max],int rowS,string lAdress)
{
	// baraye zakhire puzzle az file be arraye 
	// aval file ro to yek arraye char rikhtim , bad item haye arraye char ro be int tabdil kardim
	// to yek arraye int rikhtim
	// lPuz = Puzzle function loadPuzzle
	char charLoadPuz[rowS][cols];
	ifstream lPuzzle(lAdress);
	for(int i=0;i<rowS;i++)
	{
		for(int j=0;j<cols;j++)
		{
			lPuzzle >> charLoadPuz[i][j];
		}
	}
	for(int l=0;l<Max;l++)
	{
		int m=0;
		for(int k=0;k<cols;k +=2)
		{
			if(charLoadPuz[l][k] != '?')
			lPuz[l][m]=charToInt(charLoadPuz[l][k]);
			else
			lPuz[l][m]=0;
			m += 1;
		}
	}
}
void showPuzzle(int sPuz[][Max],int sRow,int copyPuz[][Max],int copyRows)
{
	// baraye namayesh puzzle
	// sPuz = puzzle function showPuzzle , sRow = row haye puzzle 
	cout << endl;
	cout << '\t';
	for(int k=1;k<=9;k++)
	cout << 'C'<<k<<'\t';
	cout <<endl<<endl;
	for(int i=0;i<sRow;i++)
	{
		cout << 'R'<<i+1<<"\t";
		for(int j=0;j<Max;j++)
		{	

			if(sPuz[i][j] == 0 && copyPuz[i][j]==0)
			cout <<'*'<< '?'<<'*';
			else if(sPuz[i][j] != 0 && copyPuz[i][j] ==0)
			cout <<'*'<<sPuz[i][j]<<'*';
			else if(copyPuz[i][j] != 0)
			cout <<'-'<<copyPuz[i][j]<<'-';
			if(j != (Max-1))
			cout << '\t';
			else
			cout <<"\n\n";
		}
	}
}
void fillPuz(int fPuz[][Max],int fRow,int copyPuz[][Max],int copyRow,string ans)
{
	// baraye por kardn jadval ba estefade az input haye karbar
	// fPuz = puzzle function fillPuz - frow = row haye puzzle - ans = string answer
	int row,col,value;
	row = charToInt(ans[0])-1;
	col = charToInt(ans[2])-1;
	value = charToInt(ans[4]);
	if(copyPuz[row][col] != 0)
	cout << "\nFixed values cannot be changed"<<endl;
	else
	{
		fPuz[row][col] = value;
	}
}
bool isFillPuz(int iFPuz[][Max],int iFRow)
{
	// baraye check kamel shodn jadval 
	// iFPuz = puzzle function isFillPuz - iFRow = row haye puzzle
	bool res=true;
	for(int i=0;i<iFRow;i++)
	{
		for(int j=0;j<Max;j++)
		{
			if(iFPuz[i][j] == 0)
			res = false;
		}
	}
	return res;
}
// 1- for row , 2-for col , 3-for square
bool rowChecker(int a,int rchPuz[][Max],int rchRow,int rErrorAr[],int sizeEA)
{
	// check row haye jadval , dar func puzzleChecker ( 3ta func paiin tar ) azin function estefade mikonim ke dar har
	// row tedad adad ro az 1-9 check konim , age satri bishtr az yeki az in adad dashte bashe yani be dorosti por nashode
	// eshkalat jadvar dar arraye rErrorAr zakhire mishn ,, tozih arraye rErrorAr ro dar func puzzleChecker midam
	// rchPuz = puzzle function rowChecker - rchRow = row haye puzzle - rErrorAr = row checker Error array - sizeEA = size
	// error array
	bool reS = true;
	int counter=0,rIndxArr; // rIndxArr = row index array
	for(int i=0;i<rchRow;i++)
	{
		counter = 0;
		for(int j=0;j<Max;j++)
		{
			if(rchPuz[i][j]==a)
			counter += 1;
		}
		if(counter > 1)
		{
			rIndxArr=arrayLen(rErrorAr,sizeEA);
			reS=false;
			rErrorAr[rIndxArr]=1;
			rErrorAr[rIndxArr+1]=i+1;
			rErrorAr[rIndxArr+2]=counter;
			rErrorAr[rIndxArr+3]=a;
		}
	}
	return reS;
}
bool colChecker(int b,int cchPuz[][Max],int cchRow,int cErrorAr[],int sizeEa)
{
	// check col haye jadval , dar func puzzleChecker ( 2ta func paiin tar ) azin function estefade mikonim ke dar har
	// col tedad adad ro az 1-9 check konim , age sutuni bishtr az yeki az in adad dashte bashe yani be dorosti por nashode
	// eshkalat jadvar dar arraye cErrorAr zakhire mishn ,, tozih arraye cErrorAr ro dar func puzzleChecker midam
	// cchPuz= col checker puzzle - cchRow= row haye puzzle - cErrorAr= col checker Error array - sizeEa= size error array
	bool ReS = true; // Res = result
	int Counter=0,cIndxArr;
	for(int j=0;j<cchRow;j++)
	{
		Counter = 0;
		for(int i=0;i<Max;i++)
		{
			if(cchPuz[i][j]==b)
			Counter += 1;
		}
		if(Counter > 1)
		{
			cIndxArr=arrayLen(cErrorAr,sizeEa);
			ReS=false;
			cErrorAr[cIndxArr]=2;
			cErrorAr[cIndxArr+1]=j+1;
			cErrorAr[cIndxArr+2]=Counter;
			cErrorAr[cIndxArr+3]=b;
		}
	}
	return ReS;
}
bool squareChecker(int c,int sCPuz[][Max],int PuzRow,int sErrorAr[],int sizeeA)
{
	// check squre ya 9ta morabaye jadval sodoku -- shomaresh moraba ha besorat satri anjam shode
	// mes rowChecker va colChecker agar az adad 1-9 bishtr az yeki dar har moraba vojod dashte bashe yani be dorosti
	// por nashode va eshkalat jadval dar arraye sErrorAr zakhire mishan
	// sCPuz= square Checker puzzle, PuzRow= row haye puzzle, SErrorAr= Square checker Error array, SizeeA= size error array
	bool res=true;
	int jStart = 0,iStart=0,counter=0,sIndxArr;
	for(int k=1;k<=3;k++) // 3ta satr morabaye 3taii darim
	{
		for(int n=1;n<=3;n++) // dar har satr 3ta moraba darim
		{
			counter =0;
			for(int i=iStart;i<(iStart+3);i++) // row haye har moraba
			{
				for(int j=jStart;j<(jStart+3);j++) // col haye har moraba
				{
					if(sCPuz[i][j]==c)
					{
						counter += 1;
					}
				}
			}
			if(counter > 1)
			{
				res = false;
				sIndxArr=arrayLen(sErrorAr,sizeeA);
				sErrorAr[sIndxArr]=3;
				sErrorAr[sIndxArr+1]=n*k;
				sErrorAr[sIndxArr+2]=counter;
				sErrorAr[sIndxArr+3]=c;		
			}
			
			jStart += 3;	
		}
		jStart=0;
		iStart += 3;
	}
	return res;
}
bool puzzleChecker(int chPuz[][Max],int chRow,int ErrorAr[],int size)
{
	/* estefade az 3 function bala dar yek function koli baraye check jadval
	 eshkalat jadval dar yek arraye 1 bodi zakhrie mishe be in sorat ke 
	 [r/c/s , row/col/squre , count , value ] --- > index 0 : 3ta meghad dare 1 ya 2 ya 3 
	 1-row , 2-col , 3-square ---> chon hameye error ha dar yek arraye zakhire mishan bayad kari mikardim har error
	 ghabel tamayazo az digari bashe , pas index aval ro be moshakhas krdn noe error az nazar row,col,square 
	 ekhtesas dadim ----- index 1: shomareye row/col/square jadval ro poshesh mide 
	 index 2: tedad valueii ke eshtebah por shode ro moshakhas mikone , masalan : 3ta adad 2 dar yek satr ya 2ta 
	 adad 1 dar yek square 
	 index 3: khode value ro moshakhas mikone
	 */
	 // chPuz = Puzzle function puzzleChecker, chRow = row haye puzzle, ErrorAr = Error array, size = size Error array
	bool resCheck=true,rResult = true , cResult=true,sResult=true;
	for(int k=1;k<=Max;k++)
	{
		rResult = rowChecker(k,chPuz,chRow,ErrorAr,size);
		cResult = colChecker(k,chPuz,chRow,ErrorAr,size);
		sResult = squareChecker(k,chPuz,chRow,ErrorAr,size);
		if(!(rResult && cResult && sResult))
		{
			resCheck = false;
		}
	}
	return resCheck;
}
void singleDimensionalArrayCleaner(int arr[],int size)
{
	// baraye 0 kardn khane haye yek jadval 1 bodi
	for(int i=0;i<size;i++)
	arr[i]=0;
}
void showError(int eArray[],int row)
{
	// baraye neshan dadn error haye jadval bade hal karbar ( tozihat bishtr dar func puzzleChecker dadim )
	// eArray = Error array
	int cnt=0,value=0,rowOrCol=0,numOfSquare=0; // cnt = counter 
	int Size = arrayLen(eArray,row);
	for(int i=0;i<Size;i += 4)
	{
		if(eArray[i] == 1)
		{
			rowOrCol = eArray[i+1];
			cnt = eArray[i+2];
			value = eArray[i+3];
			cout << "Row: "<< rowOrCol << " has "<<cnt << " numbers of: "<<value<<endl;
		}
		else if(eArray[i] == 2)
		{
			rowOrCol = eArray[i+1];
			cnt = eArray[i+2];
			value = eArray[i+3];
			cout << "Column: "<<rowOrCol<< " has "<<cnt<<" numbers of: "<<value<<endl;
		}
		else if(eArray[i] == 3)
		{
			numOfSquare=eArray[i+1];
			cnt = eArray[i+2];
			value = eArray[i+3];
			cout <<"Square: "<< numOfSquare << " has "<<cnt << " numbers of: "<<value<<endl;
		}
	}
}
void availableOptions(int aOPuz[][Max],int aORow,int aArray[][12],int size)
{
	// baraye peyda krdn available option haye yek khane khali ( khat 136-163 kamel tozih dadim ) 
	// in option haro dar yek arraye 2 bodi zakhire mikonim be in format :
	// [[row_1 - col_1 - count_of_options_1 - option1 - option2-...] , [ row_2 - col_2 .....],[....]...]
	/*
	har index arrayemon , yek arraye bare yek khoneye khali hastesh ke khode on arraye indexash injuri moarefi shodn :
	
	index0:  row khone khali , index1: col khone khali , index2: tedad option haye mored ghabol baraye on khone
	index3 ta index11 -> option haye mored ghabol ( 9ta index be in ha ekhtesas dadim chon option ha mitone had axar be 9ta
	berese (1-9)) 
	*/
	// aOPuz = available option Puzzle, aORow = row haye puzzle, aArray = available option array, size = size aArray
	arrayCleaner2(aArray,size);
	int Opt[Max],numOfItems,l=0; // Opt = option array
	singleDimensionalArrayCleaner(Opt,Max);
	for(int i=0;i<aORow;i++)
	{
		for(int j=0;j<Max;j++)
		{
			if(aOPuz[i][j]==0)
			{
				singleDimensionalArrayCleaner(Opt,Max);
				for(int k=1;k<=9;k++) // adad 1-9 ro be onvane option be khone ha midim va ba func aOChecker 
				// emtehanesh mikonim ( tozih dar aOChecker )
				{
					if(aOChecker(k,aOPuz,aORow,i,j))
					{
						int len = arrayLen(Opt,Max);
						Opt[len]=k;
					}
				}
				numOfItems = arrayLen(Opt,Max);
				aArray[l][0]=i;
				aArray[l][1]=j;
				aArray[l][2]=numOfItems;
				int m =0;
				for(int i = 3;i<12;i++)
				{
					if(m < numOfItems)
					aArray[l][i]=Opt[m];
					else
					aArray[l][i]=0;
					m++;
				}
				l += 1;
			}
		}
	}
}
bool aOChecker(int a,int aOCPuz[][Max],int aOCRow,int oRow,int oCol)
{
	/* available option checker : ba gozashtn adad 1-9 dar khane haye khali moshakhas mikonim aya in adad 
	tavanaii gharar gereftn dar on khone ro daran ya kheir , aval nesbat be ham satri haye khone khali check mikonim
	dovom nesbat be ham sotoni haye on khone khali va sevom ham nesbat be squarei ke on khone khali darash gharar dare
	*/
	// aOCPuz= available option checker Puzzle, aOCRow= row puzzle, oRow= row item mored check, oCol= col item mored check
	int counter=0,cRow,cCol;
	bool result = true;
	// for checking its row
	for(int j=0;j<Max;j++)
	{
		if(aOCPuz[oRow][j]==a)
		{
			counter += 1;
			break;
		}
	}
	// for checking its col
	if(counter == 0)
		for(int i=0;i<aOCRow;i++)
		{
			if(aOCPuz[i][oCol]==a)
			{
				counter += 1;
				result = false;
			}
		}
	else
	{
		result = false;
	}
	// for checking its square
	// dar inja ba tavajoh be mogheiiat khoneye khali moshakhas mikonim dar kodom square jadval gharar dare 
	// cRow = row shoroee square (masalan row 1-3 ya 4-6 ya 7-9 ) 
	// cCol = col shoroee square (masalan col 1-3 ya 4-6 ya 7-9 )
	if( counter == 0 )
	{
	
		if(oRow == 0 || oRow == 3 || oRow == 6)
		cRow = oRow;
		else if(oRow == 1 || oRow == 4 || oRow == 7)
		cRow = oRow - 1;
		else if(oRow == 2 || oRow == 5 || oRow == 8)
		cRow = oRow - 2;
		// col
		if(oCol == 0 || oCol == 3 || oCol == 6)
		cCol = oCol;
		else if(oCol == 1 || oCol == 4 || oCol == 7)
		cCol = oCol - 1;
		else if(oCol == 2 || oCol == 5 || oCol == 8)
		cCol = oCol - 2;
		// mogheiiat square ro darim , mitonim option mored nazaro tosh check konim
		for(int j=cCol;j<=(cCol+2);j++)
		{
			for(int i= cRow;i<=(cRow+2);i++)
			{
				if(aOCPuz[i][j]==a)
				result = false;
			}
		}
	}
	return result;
}
void singleOptionSolver(int sOSPuz[][Max],int sOSRow,int aOptions[][12],int aOpRow)
{
	// method gofte shode dar khat 147 ro ba in function piade mikonim 
	// sOSPuz = single option solver puzzle, sOSRow= row haye puzzle, aOption = available option array, aOpRow = aOption row 
	availableOptions(sOSPuz,sOSRow,aOptions,aOpRow); // update availableOptions
	for(int i=0;i<aOpRow;i++)
	{
		if(aOptions[i][2]== 1)
		{
			sOSPuz[aOptions[i][0]][aOptions[i][1]]=aOptions[i][3];
		}
	}
	availableOptions(sOSPuz,sOSRow,aOptions,aOpRow); // update availableOptions
}
void singleRowOptionChecker(int sROPuz[][Max],int rowPuz,int sROptions[][12],int sRORow)
{
	// method gofte shode dar khat 150 ro ba in function piade mikonim
	// sROPuz= single row option checker Puzzle, rowPuz= row haye puzzle, sROptions= available options, sRORow= row sROption
	int nextRow=0,i=0,count =0,col,indxStart,indxEnd;
	for(int r=0;r<rowPuz;r++) // baraye peymayesh row 
	{
		findIndexRow(sROptions,sRORow,r,indxStart,indxEnd); // dar khode func tozih dade shode
		for(int n=1;n<=Max;n++)
		{
			count =0;
			for(int i=indxStart;i<=indxEnd;i++)	
				for(int j=3;j<=9;j++)
				{
					if(sROptions[i][j]==n)
					{
						count += 1;
						col = sROptions[i][1];
					}
				}		
			if(count == 1)
			{
				sROPuz[r][col]=n;
			}
		}
	}
	availableOptions(sROPuz,rowPuz,sROptions,sRORow);	// update availableOptions
}
void singleColOptionChecker(int sCOPuz[][Max],int RowPuz,int sCOptions[][12],int sCORow)
{
	// method gofte shode dar khat 155 ro ba in function piade mikonim
	// sCOPuz= single col option checker Puzzle, RowPuz= row haye puzzle, sCOptions= available options, sCORow= row sROption
	int indxArray[Max];
	singleDimensionalArrayCleaner(indxArray,Max);
	int nextCol=0,i=0,Count=0,row,Size=0;
	for(int c=0;c<Max;c++) // baraye peymayesh col
	{
		findIndexCol(sCOptions,sCORow,indxArray,Max,c,Size); // dar khode func tozih dade shode
		for(int N=1;N<=Max;N++)
		{
			Count =0;
			for(int i=0;i<Size;i++)
			{
				for(int j=3;j<=9;j++)
				{
					if(sCOptions[indxArray[i]][j]==N)
					{
						Count += 1;
						row = sCOptions[indxArray[i]][0];
					}
				}
			}
			if(Count == 1)
			{
				sCOPuz[row][c]=N;
			}
		}
		
	}
	availableOptions(sCOPuz,RowPuz,sCOptions,sCORow); // update availableOptions
}
void findIndexRow(int optionArray[][12],int row,int numOfRow,int& startingIndex,int& endingIndex)
{
	// index haye marbot be har row dar arraye avaiable option ra ba in func peyda mikonim
	// masalan index haye 0ta 3 marbot be row 1 , index 7-10 marbot be row 3...
	// az onjaii ke arraye avaiable option bar asas row por shodn , index haye marbot be row x , poshte ham amadan
	int i=0;
	while(optionArray[i][0]==numOfRow && i<row)
	{
		i++;
	}
	startingIndex = i; // avalin index az arraye available option baraye row x
	while(optionArray[i][0]==numOfRow && i<row)
	{
		i++;
	}
	endingIndex = (i-1); // akharin index az arraye available option baraye row x
	
}
void findIndexCol(int optionArray[][12],int row,int IndexArray[],int size,int numOfCol,int& NumberOfIndexes)
{
	// index haye marbot be har col dar arraye avaiable option ra ba in func peyda mikonim
	// az onjaii ke arraye available option bar asas row ha por shode ( masalan index haye 0-3 marbot be yek row hastn )
	// va index haye col x poshte ham nistn, bayad yek arraye az index haye col x dorost konim  
	// masalan index haye {1,5,8} marbol be col x hastn
	int indx=0;
	for(int i=0;i<row;i++)
	{
		if(optionArray[i][1]==numOfCol)
		{
			IndexArray[indx]=i;
			indx++;
		}	
	}
	NumberOfIndexes = indx;
}
int twoDemArrayLen(int ar[][12],int row)
{
	// baraye peyda krdn size yek arraye 2 bodi be tedad col 12
	int j=0;
	for(int i=0;i<row;i++)
	{
		int len = arrayLen(ar[i],12);
		if(len==0)
		{
			break;
		}
		else
		{
			j+=1;
		}
	}
	return j;
}
int arrayLen(int ar[],int size)
{
	// baraye peyda kardn size yek arraye 1 bodi
	int cnt=0;
	for(int i=0;i<size;i++)
	{
		if(ar[i] > 0)
		cnt += 1;
	}
	return cnt;
}
void adressSolvedPuzzle(string& adress)
{
	// baraye ezafe kardn "_Solved.txt" be adress vared shode tavasot karbar va zakhire file jadid be onvan jadval hal shode
	int size= stringLenght(adress);
	string temp;
	for(int i=0;i<(size-4);i++)
	{
		temp +=adress[i];
	}
	temp += "_Solved.txt";
	adress = temp;	
}