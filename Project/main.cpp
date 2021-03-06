#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <fstream>
using namespace std;

void spel_Instructies(){
	cout << endl << "   Welkom bij 'Hunt de Wumpus'" << endl;
	cout << " De Wumpus leeft in een grot met 20 kamers, elke kamer is verbonden met 3 andere kamers." << endl;
	cout << endl << "--------------------------------------------------------------------------------------" << endl << endl; 
		cout << "\t Obstakels:" << endl;
			cout << "\t\t 1. De Super Vleermuizen: Als je in dezelfde kamer komt als de vleermuis," << endl;
			cout << "\t\t    wordt je naar een willekeurige kamer toe gevlogen." << endl << endl;
			cout << "\t\t 2. De Valkuilen: Als je in dezelfde kamer komt als de valkuil val je naar je dood..." << endl << endl;
			cout << "\t\t 3. De Wumpus: Als je in dezelfde kamer komt als de Wumpus wordt je opgegeten," << endl;
			cout << "\t\t    en het heeft geen last van obstakels" << endl << endl;
		cout << "\t De Speler:" << endl;
		cout << "\t Elke ronde mag je bewegen of schieten." << endl;
			cout << "\t\t 1. Bewegen: Je kan telkens naar 1 kamer lopen via een tunnel." << endl;
			cout << "\t\t    De kamers waar je naartoe kan lopen worden aangegeven in het spel." << endl;
			cout << "\t\t 2. Schieten: Je start met 5 pijlen. Als je geen pijlen hebt verlies je." << endl;
			cout << "\t\t    Schiet je in de kamer waar de Wumpus zich bevindt heb je gewonnen." << endl << endl;
		cout << "\t Waarschuwingen:" << endl;
		cout << "\t 1. Als je 1 kamer verwijdert bent van een valkuil of een vleermuis, krijg je de volgende melding:" << endl;
			cout << "\t\t Valkuil: 'Ik voel een koude rilling'"<< endl;
			cout << "\t\t Vleermuis: 'Ik hoor gefladder'" << endl;
		cout << "\t 2. Als je 1 of 2 kamers verwijdert bent van de Wumpus, krijg je de volgende melding:" << endl;
			cout << "\t\t Wumpus: Ik ruik de Wumpus" << endl;
		cout << "\t 3. Je kan ook een dubbele waarschuwing krijgen, die krijg je door:" << endl;
			cout << "\t\t Als je 1 kamer verwijdert bent van de Super Vleermuis EN de Valkuil." << endl;
			cout << "\t\t Als je 1 kamer verwijdert bent van de Super Vleermuis, de Valkuil EN de Wumpus zit 1 of 2 kamers verderop." << endl;
			cout << "\t\t Als je 1 kamer verwijdert bent van de Super Vleermuis EN de Wumpus zit 1 of 2 kamers verderop." << endl;
			cout << "\t\t Als je 1 kamer verwijdert bent van de Valkuil EN de Wumpus zit 1 of 2 kamers verderop." << endl;
}

bool verbondenKamers(vector<vector<int>> rooms, int index, int controle, int variatie){
	if(variatie == 0){ // Or
		if(controle == rooms[index][0] || controle == rooms[index][1] || controle == rooms[index][2]) 
			return 1;
		else
			return 0;
	}
	else if(variatie == 1){ // Nor
		if(controle != rooms[index][0] || controle != rooms[index][1] || controle != rooms[index][2]) 
			return 1;
		else
			return 0;
	}
	else if(variatie == 2){ // Nand
		if(controle != rooms[index][0] && controle != rooms[index][1] && controle != rooms[index][2]) 
			return 1;
		else
			return 0;
	}
	else if(variatie == 3){ // And
		if(controle == rooms[index][0] && controle == rooms[index][1] && controle == rooms[index][2]) 
			return 1;
		else
			return 0;
	}
	else if(variatie == 4){ // Double Or
		if(controle == rooms[rooms[index][0]][0] || controle == rooms[rooms[index][1]][0] || controle == rooms[rooms[index][2]][0] || controle == rooms[rooms[index][0]][1] || controle == rooms[rooms[index][1]][1] || controle == rooms[rooms[index][2]][1] || controle == rooms[rooms[index][0]][2] || controle == rooms[rooms[index][1]][2] || controle == rooms[rooms[index][2]][2]) 
			return 1;
		else
			return 0;
	}
	else{
		cout << "Ongeldige Variatie"; 
		return 0;
	}		
}

int pijlen(int &pijl_Count){
	if(pijl_Count > 0)
		return pijl_Count -= 1;
	else
		return pijl_Count;
}

int computerInputSlim(vector<vector<int>> rooms, int index, int input, vector<int> &avoidKamers){
	if(verbondenKamers(rooms, index, avoidKamers[0], 0))
		input = (avoidKamers[0]) + 20;
	else 
		input = rooms[index][rand() % 3];
	while(input == avoidKamers[0] || input == avoidKamers[1] || input == avoidKamers[2] || input == avoidKamers[3] || input == avoidKamers[4])
		input = rooms[index][rand() % 3];
	Sleep(1000);
	return input;
}

int spel(vector<vector<int>> rooms, int index, int input, int wumpus, int valKuil, int valKuil1, int bat, int bat1, int pijl, int variatie, int &win, vector<int> &avoidKamers){
	cout << endl << "(Typ '-1' als je wilt stoppen met spelen, Typ '-3' als je de wumpuslocatie als hint wilt zien snoepie!)" << endl;
	while(input != -1){
		if(input == -2 && wumpus != index && pijl != 0){ // Game-TUI
			cout << endl << "--------------------------------------------------------------------------------------" << endl;
			cout << endl << "Je zit nu in kamer: " << index << endl << "Deze kamer is verbonden met: ";
			for(int j = 0; j < 3; j++){ 
				cout << rooms[index][j] << " ";
			}
			cout << endl << endl << "--------------------------------------------------------------------------------------" << endl;
			if((verbondenKamers(rooms, index, bat, 0) || verbondenKamers(rooms, index, bat1, 0)) || (verbondenKamers(rooms, index, valKuil, 0) || verbondenKamers(rooms, index, valKuil1, 0)) ||  verbondenKamers(rooms, index, wumpus, 0) || verbondenKamers(rooms, index, wumpus, 4)){
				if((verbondenKamers(rooms, index, bat, 0) || verbondenKamers(rooms, index, bat1, 0)) && verbondenKamers(rooms, index, wumpus, 1))
					cout << endl << "Waarschuwing: Ik hoor gefladder!" << endl; 
				if((verbondenKamers(rooms, index, valKuil, 0) || verbondenKamers(rooms, index, valKuil1, 0)) && verbondenKamers(rooms, index, wumpus, 1))
					cout << endl << "Waarschuwing: Ik voel een koude rilling!" << endl;
				if(verbondenKamers(rooms, index, wumpus, 0) || verbondenKamers(rooms, index, wumpus, 4))
					cout << endl << "Waarschuwing: Ik ruik de Wumpus" << endl;
			}
			else
				cout << endl << "Niks aan de hand" << endl;
			cout << endl << "--------------------------------------------------------------------------------------" << endl;
			cout << endl << "Naar welke kamer zou je willen lopen of schieten" << endl << "Als je wilt lopen voer je de gewenste kamernummer in" << endl << "Als je wilt schieten voer je de gewenste kamernummer +20 in: ";
			if(variatie == 0)
				cin >> input;
			else if(variatie == 1){
				input = computerInputSlim(rooms, index, input, avoidKamers);
				cout << input;
			}
				
		}
		else if(input == -3){ // Cheat-menu
			cout << endl << "--------------------------------------------------------------------------------------" << endl;
			cout << endl << "Hint: De Wumpus zit in kamer: " << wumpus << endl;
			input = -2;
		}
		else if(pijl == 0){ // Pijlen 0 Scenarios.
			cout << "Je pijlen zijn op... Maar in een wanhopige poging zoek je de Wumpus op." << endl;
			cout << "Je vindt de Wumpus en daagt het uit. Met een boog zonder pijlen sta je oog in oog met de Wumpus." << endl;
			cout << "Je breekt je boog, om een scherp stuk hout te krijgen. Je vraagt jezelf af hoe dit zou aflopen..." << endl;
			while(input < 0)
				input = rand() % 1000;
			if(input == 0){ // Scenario: Pijlen == 0, Wumpus Dood. (W)
				cout << "De Wumpus is in een oogwenk bij je maar je was hierop voorbereid." << endl;
				cout << "Je steekt met het stuk hout de wumpus in zijn keel en duwt hem op de grond." << endl;
				cout << "Je houd de Wumpus op de grond terwijl je jouw houtstuk diep in zijn keel boort." << endl;
				cout << "De Wumpus ademt niet meer... Je hebt ondanks dat je geen pijlen had gewonnen. Het lijkt wel een mirakel, een 1 op 1000 kans..." << endl;
				cout << "Game Over." << endl;
				cout << endl << "--------------------------------------------------------------------------------------" << endl;
				cout << endl << "Storyline Copyrighted by Ivo Berger 2020" << endl;
				win++;
				input = -1;
			}
			else{ // Scenario: Pijlen == 0, Speler Dood. (L)
				cout << "Helaas... In een oogwenk is de Wumpus bij je, het slaat de boog uit je handen en pakt je bij je keel." << endl;
				cout << "Voordat je het weet wordt alles donkerder, Je krijgt geen adem meer... 'Vaarwel vrede wereld' zijn je laatste woorden..." << endl;
				cout << "De Wumpus breekt je nek." << endl;
				cout << "Game Over." << endl;
				cout << endl << "--------------------------------------------------------------------------------------" << endl;
				cout << endl << "Storyline Copyrighted by Ivo Berger 2020" << endl;
			}
			input = -1;
		}		
		else if(input > 19){ // Schiet mogelijkheden
			if(((input - 20) == wumpus) && verbondenKamers(rooms, index, wumpus, 0)){ // Scenario: Speler heeft de Wumpus gedood. (W)
				cout << endl << "--------------------------------------------------------------------------------------" << endl;
				cout << endl << "Je hebt je pijl geschoten. Je pijl spietste de Wumpus recht door zijn hoofd.";
				cout << endl << "Je geloofde je ogen niet. De Wumpus, degene naar wie je al 5 jaar jaagt... Is dood!";
				cout << endl << "Gevuld met vreugde en opluchting verlaat je de grot... Je hebt gewonnen."; 
				cout << endl << "Game Over." << endl;
				cout << endl << "--------------------------------------------------------------------------------------" << endl;
				cout << endl << "Storyline Copyrighted by Ivo Berger 2020" << endl;
				win++;
				input = -1;
			}
			else if(verbondenKamers(rooms, index, (input - 20), 2) || index == input - 20){ // Error Controle (Schieten)
				cout << endl << "--------------------------------------------------------------------------------------" << endl;
				if(index == input - 20)
					cout << endl << "Error: Je schiet jezelf!" << endl;
				else 
					cout << endl << "Error: Ongeldige Keuze!!" << endl;
				cout << endl << "--------------------------------------------------------------------------------------" << endl;
				cout << endl << "Naar welke kamer zou je willen lopen of schieten" << endl << "Als je wilt lopen voer je de gewenste kamernummer in" << endl << "Als je wilt schieten voer je de gewenste kamernummer +20 in: ";
				cin >> input;				
			}
			else{ // Scenario: Speler mist de Wumpus, Wumpus verplaatst zich.
				cout << endl << "--------------------------------------------------------------------------------------" << endl;
				cout << endl << "De Wumpus was niet in kamer " << (input - 20) << ", de Wumpus is ontwaakt en is naar een willekeurige kamer verplaatst." << endl;
				pijlen(pijl);
				cout << "Je hebt nog " << pijl << " pijl(en) over."<< endl;
				input = wumpus;
				while(wumpus == input) 
					input = rand() % 20;
				wumpus = input;
				input = -2;
			}
		}
		else if(wumpus == index){ // Scenario: Dood door 'Wumpus', Wumpus and speler automagically in zelfde kamer. (L)
			avoidKamers[0] = input;
			cout << endl << "--------------------------------------------------------------------------------------" << endl;
			cout << endl << "De Wumpus en jij komen in dezelfde donkere en grote kamer terecht." << endl;
			cout << "De Wumpus en jij kijken elkaar heel droog aan. De Wumpus realiseert wie jij bent en komt achter je aan." << endl;
			cout << "Jij realiseert je nu ook wat het is, de Wumpus! Je probeert weg te rennen maar je struikelt." << endl;
			cout << "Er is niks wat je kan doen. Je kan alleen hopen op een snel einde... de Wumpus haalt je uit." << endl;
			cout << "Game Over." << endl;
			input = -1;
		}
		else if(index == input || cin.fail() || verbondenKamers(rooms, index, input, 2)){ // Error Controle (Lopen)
			cout << endl << "--------------------------------------------------------------------------------------" << endl;
			if(cin.fail()){
				cout << endl << "Error: Foutieve Syntax!" << endl; 
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			else if(index == input)
				cout << endl << "Error: Je zit al in die kamer!" << endl;
			else if(verbondenKamers(rooms, index, input, 2))
				cout << endl << "Error: Ongeldige Keuze!" << endl;
			cout << endl << "--------------------------------------------------------------------------------------" << endl;
			cout << endl << "Naar welke kamer zou je willen lopen of schieten" << endl << "Als je wilt lopen voer je de gewenste kamernummer in" << endl << "Als je wilt schieten voer je de gewenste kamernummer +20 in: ";
			cin >> input;
		}
		else if(wumpus == input){ // Scenario: Dood door 'Wumpus' kamer te benaderen. (L)
			avoidKamers[0] = input;
			cout << endl << "--------------------------------------------------------------------------------------" << endl;
			cout << endl << "Je komt in een donkere, stinkende en grote kamer terecht. Je vraagt jezelf af wat er zo erg kan stinken." << endl;
			cout << "Je loopt en kijkt rond in de kamer, maar je stoot tegen iets stevigs aan." << endl;
			cout << "Het grote en stinkende monster staat op en op dat moment realiseer je dat het al telaat is." << endl;
			cout << "De Wumpus! Je probeert weg te rennen maar je struikelt." << endl;
			cout << "Er is niks wat je kan doen. Je kan alleen hopen op een snel einde..." << endl;
			cout << "Game Over." << endl;
			input = -1;
		}
		else if((valKuil == input || valKuil1 == input) && wumpus != input){ // Scenario: Dood door 'bodemloze kuil'. (L)
			if(input == valKuil) 
				avoidKamers[1] = input;
			else 
				avoidKamers[2] = input;
			cout << endl << "--------------------------------------------------------------------------------------" << endl;
			cout << endl << "Je bent altijd zo voorzichtig geweest... Je bent altijd alert geweest, alleen dit keer niet..." << endl;
			cout << "Je struikelt over een stuk steen, je verliest je balans en voordat je het weet..." << endl;
			cout << "Val je zo in een bodemloze kuil..." << endl;
			cout << "Game Over." << endl;
			input = -1;
		}
		else if((bat == input || bat1 == input) && wumpus != input){ // Scenario: Verplaats door 'super vleermuis'.
			if(input == bat) 
				avoidKamers[3] = input;
			else 
				avoidKamers[4] = input;
			while(bat == input || bat1 == input) 
				input = rand() % 20;
			cout << endl << "--------------------------------------------------------------------------------------" << endl;
			cout << endl << "Je komt een donkere kamer binnen. Je voelt een druppel op je hoofd vallen, het was alleen geen water maar kwijl!" << endl;
			cout << "een super vleermuis grijpt met zijn grote poten jou op en sleurt jou door de kamers van de grot." << endl;
			cout << "Je slaat de vleermuis meerdere keren op zijn neus, na de vierde keer lukt het om jezelf los te wikkelen van de vleermuis." << endl;
			cout << "De vleermuis vliegt weg." << endl;
			cout << "Je valt op de grond, nog steeds in dezelfde grot, met nog steeds dezelfde missie..." << endl;
			cout << "Dood de Wumpus." << endl;
			cout << endl << "Je bent in kamer: " << input << " Terecht gekomen." << endl;
			index = input;
			input = -2;
		}
		else{ // Lopen door de matrix
			index = input;
			input = -2;
		}
	}
	cout << endl << "--------------------------------------------------------------------------------------" << endl;
	cout << endl << "Dit project is mede-mogelijk gemaakt door 'int saus' free mijn niffo saus." << endl;
	cout << endl << "--------------------------------------------------------------------------------------" << endl;
	return win;
}

vector<unsigned int> configureerTraps(const unsigned int start){
	unsigned int valKuil = start, valKuil1 = start, bat = start, bat1 = start, wumpus = start;
    vector<unsigned int> trapRooms;
    while(wumpus == start)
		wumpus = rand() % 20;
	while(valKuil == start)
		valKuil = rand() % 20;
    while(valKuil1 == start || valKuil1 == valKuil)
        valKuil1 = rand() % 20;
    while(bat == start || bat == valKuil || bat == valKuil1)
        bat = rand() % 20;
    while(bat1 == start || bat1 == valKuil || bat1 == valKuil1 || bat1 == bat)
        bat1 = rand() % 20;
    trapRooms.push_back({wumpus});trapRooms.push_back({valKuil});trapRooms.push_back({valKuil1});trapRooms.push_back({bat});trapRooms.push_back({bat1});
	return trapRooms;
}

vector<vector <int>> configuratieRandomKamers(vector<vector <int>> kamers){
	return kamers; // W.I.P.
}

void configuratie(const string &File){
	vector<vector <int>> rooms= {
								{10, 11, 19},  	//0
								{2, 10, 11},   	//1
								{1, 3, 12},		//2
								{2, 4, 13},		//3
								{3, 5, 14},		//4
								{4, 6, 15},		//5
								{5, 7, 16},		//6
								{6, 8, 17},		//7
								{7, 9, 18},		//8
								{8, 10, 19},	//9
								{0, 1, 9},		//10
								{0, 1, 12},		//11
								{2, 11, 13},	//12
								{3, 12, 14},	//13
								{4, 13, 15},	//14
								{5, 14, 16},	//15
								{6, 15, 17},	//16
								{7, 16, 18},	//17
								{8, 17, 19},	//18
								{0, 9, 18}};	//19
	ofstream writeFile(File);
	if(writeFile.is_open()){
		for(unsigned int i = 0; i < rooms.size(); i++){
			for(unsigned int j = 0; j < rooms[i].size(); j++){
				writeFile << rooms[i][j] << " " ;
			}
			writeFile << endl;
		}
	unsigned int configureerStart = rand() % 20;
	vector<unsigned int> traps = configureerTraps(configureerStart);
	writeFile << -1 << " " << configureerStart << endl;
	for(unsigned int i = 0; i < 5; i++){
		if(i == 0)
			writeFile << -2 << " " << traps[i] << endl;	
		else if(i == 1 || i == 2){
			writeFile << -3 << " " << traps[i] << " " << -3 << " " << traps[i + 1] << endl;
			i++;
		}
		else{
			writeFile << -4 << " " << traps[i] << " " << -4 << " " << traps[i + 1] << endl;
			i++;
		}
	}
	writeFile.close();
    }
	else
        cout << "Can't open file" << endl;
}

vector<vector<int>> configuratie_Rooms_Lezen(vector<vector<int>> &rooms, const string &File){
	ifstream readFile(File);
	int arr[60], cnt = 0, x = 0;
	
	if(readFile.is_open()){
		while (cnt < 60 && readFile >> x)
			arr[cnt++] = x;
		for (int i = 0; i < 60; i += 3)
			rooms.push_back({arr[i], arr[i+1], arr[i+2]});		
	readFile.close();
    }
	else
        cout << "Can't open file" << endl;
	return rooms;
}

vector<int> configuratie_TrapRooms_Lezen(vector<int> &trapRooms, const string &File){
	ifstream readFile(File);
	int arr[72], cnt = 0, x = 0;
	
	if(readFile.is_open()){
		while(cnt < 72 && readFile >> x)
			arr[cnt++] = x;
		for(int i = 60; i < 72; i += 2){
			if(arr[i] == -1)
				trapRooms.push_back({arr[i + 1]});
			else if(arr[i] == -2)
				trapRooms.push_back({arr[i + 1]});
			else if(arr[i] == -3)
				trapRooms.push_back({arr[i + 1]});
			else if(arr[i] == -4)
				trapRooms.push_back({arr[i + 1]});
		}		
	readFile.close();
    }
	else
        cout << "Can't open file" << endl;
	return trapRooms;
}

void highscoreOverwrite(int beurten, string naam){
	ofstream writeFile("Project/highscores.txt");
	writeFile << beurten << " " << naam; 
	writeFile.close();
}

void highscoreControle(int beurten){
    ifstream readFile("Project/highscores.txt");
    string line, naam;

    if(readFile.is_open()){
        if(readFile.peek() == ifstream::traits_type::eof()){ //Bron: https://stackoverflow.com/questions/26228424/how-to-detect-an-empty-file-in-c
            cout << "Je hebt de nieuwe Highscore!!" << endl;
            cout << "De nieuwe Highscore is: " << beurten << endl;
            cout << "Onder welke naam zou je jouw Highscore willen opslaan: ";
            cin >> naam;
            highscoreOverwrite(beurten, naam);
        }
        else{
            while(getline(readFile, line)){
                string substring = line.substr(0, 1);
                int oudeHighscore = stoi(substring);
                
                if(oudeHighscore > beurten){
                    cout << "Je hebt de nieuwe Highscore!!" << endl;
                    cout << "De oude Highscore was: " << oudeHighscore << " van "; 
                    for(int i = 2; line[i]; i++){
                        cout << line[i];
                    }
                    cout << endl << "De nieuwe Highscore is: " << beurten << endl;
                    cout << "Onder welke naam zou je jouw Highscore willen opslaan: ";
                    cin >> naam;
                    highscoreOverwrite(beurten, naam);
                }
                else if(oudeHighscore == beurten)
                    cout << "Je score was gelijk aan die van de Highscore, dus gg: Score - " << beurten << ", " << oudeHighscore << endl;
                else
                  cout << "De oude Highscore is niet verbeterd: " << endl << "Je score is: " << beurten << endl << "De Highscore is: " << oudeHighscore << endl;
				cout << endl << "--------------------------------------------------------------------------------------" << endl;
            }
        }
        readFile.close();
    }
    else
        cout << "Can't open file" << endl;
}

int main(){
	srand(time(NULL));
	vector<vector<int>> rooms = {};
	vector<int> trapRooms = {}, avoidKamers = {-1,-1,-1,-1,-1};
	string file = "Project/configuratie.txt";
	int state = 0, beurten = 0, win = 0;
	cout << "--------------------------------------------------------------------------------------" << endl;
	cout << endl << "Als je uitleg wil voer '1' in, als je een nieuw doolhof wil voer '2' in, "<< endl << "als jij wil spelen voer '3' in of als je wil dat het spel zichzelf uit laat spelen voer '4' in: "; 
	cin >> state;
	cout << endl << "--------------------------------------------------------------------------------------" << endl;
	
	while(state != -1){
		if(state == 1){ // Game Instructies
			spel_Instructies();
			cout << endl << "--------------------------------------------------------------------------------------" << endl;
			cout << endl << "Als je uitleg wil voer '1' in, als je een nieuw doolhof wil voer '2' in, "<< endl << "als jij wil spelen voer '3' in of als je wil dat het spel zichzelf uit laat spelen voer '4' in: "; 
			cin >> state;
			cout << endl << "--------------------------------------------------------------------------------------" << endl;
		}
		else if(state == 2){ // Random Configuratie Generator
			ofstream readFile("Project/highscores.txt", ios::trunc); //Bron: https://www.reddit.com/r/cpp_questions/comments/9jq3i6/delete_data_in_file_c/
			configuratie(file);
			cout << "Configuratie aangemaakt:" << endl << "Als jij wil spelen voer '1' in als je wil dat het spel zichzelf uitspeelt voer '2' in: ";
			cin >> state;
			cout << endl << "--------------------------------------------------------------------------------------" << endl;
			if(state == 1)
				state = 3;
			else if(state == 2)
				state = 4;
			else
				state = 0;
		}
		else if(state == 3){ // Speler: Persoon
			beurten++;
			configuratie_Rooms_Lezen(rooms, file);
			configuratie_TrapRooms_Lezen(trapRooms, file);
			spel(rooms, trapRooms[0], -2, trapRooms[1], trapRooms[2], trapRooms[3], trapRooms[4], trapRooms[5], 5, 0, win, avoidKamers);
			state = -10;
		}
		else if(state == 4){ // Speler: computerSlim
			beurten++;
			configuratie_Rooms_Lezen(rooms, file);
			configuratie_TrapRooms_Lezen(trapRooms, file);
			spel(rooms, trapRooms[0], -2, trapRooms[1], trapRooms[2], trapRooms[3], trapRooms[4], trapRooms[5], 5, 1, win, avoidKamers);
			if (win != 1)
				state = 4;
			else 
				state = -10;
		}
		else if(state == -10){ // Statistiek: W.I.P. PS(Niet Gered, gegaan voor alternatief)
			cout << endl;
			if (win != 1)
				cout << "Je hebt zojuist verloren! ";
			else{
				highscoreControle(beurten);
				win = 0;
				beurten = 0;
			}
			cout << endl << "Wil je nog een keer spelen? voer dan '1' in of als je wil dat het spel zichzelf uit laat spelen voer '2' in: ";
			cin >> state;
			cout << endl << "--------------------------------------------------------------------------------------" << endl;
			if(state == 1)
				state = 3;
			else if(state == 2)
				state = 4;
			else
				state = 0;
		}
		else{ // Error Controle
			if(cin.fail()){
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			cout << endl << "Error: Dat is geen geldige optie!" << endl; 
			cout << endl << "--------------------------------------------------------------------------------------" << endl; 
			cout << endl << "Als je uitleg wil voer '1' in, als je een nieuw doolhof wil voer '2' in, "<< endl << "als jij wil spelen voer '3' in of als je wil dat het spel zichzelf uit laat spelen voer '4' in: "; 
			cin >> state;
			cout << endl << "--------------------------------------------------------------------------------------" << endl;
		}
	}
	return 0;
}