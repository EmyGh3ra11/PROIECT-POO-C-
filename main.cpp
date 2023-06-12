#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "Player.h"
#include "Team.h"
#include "Match.h"

using namespace std;

vector<Player> CitireDinFisier(const string& filename, Team& team1, Team& team2)
{
    vector<Player> players;
    ifstream inputFile(filename);   //deschidera fisierului

    if (inputFile.is_open())
    {
        string name, age, position, goalScored;
        while (getline(inputFile, name) && getline(inputFile, age) && getline(inputFile, position) && getline(inputFile, goalScored))//pentru fiecare linie din fisier ii este atribuita o valoare
        {
            players.emplace_back(name, age, position, goalScored);
        }
        inputFile.close(); // inchiderea fisierului

        // Afisarea listei de jucatori din fisier
        cout << "Jucatori disponibili pentru adaugare in echipe: " << endl;
        for (const auto& player : players)
        {
            cout << player.getName() << endl;
        }

        // Asociere jucători cu echipe
        for (const auto& player : players)
        {
            cout << "In ce echipa vrei sa pui jucatorul " << player.getName() << "?" << endl;
            cout << "1. " << team1.getName() << endl;
            cout << "2. " << team2.getName() << endl;
            string opt;
            cin >> opt;

            if (opt == "1")
            {
                team1.AddPlayer(player);
                cout << "Jucatorul " << player.getName() << " a fost adaugat in echipa " << team1.getName() << endl;
            }
            else if (opt == "2")
            {
                team2.AddPlayer(player);
                cout << "Jucatorul " << player.getName() << " a fost adaugat in echipa " << team2.getName() << endl;
            }
            else
            {
                cout << "Nu mai sunt echipe" << endl;
            }
        }
    }
    else
    {
        cout << "Nu am putut deschide fisierul " << filename << endl;
    }

    return players;
}

int main()
{
    Player player;
    Team team;
    Team team1;
    Team team2;
    Match match;
    vector<Player> players;

    ifstream file("jucatori.txt");
    string line;

    string option;
    do
    {
        cout << "\n====================   BINE AI VENIT IN MENIU    ==================\n" << endl;
        cout << "       I. Introdu Playerul" << endl;
        cout << "       E. Introdu Echipele" << endl;
        cout << "       A. Afiseaza Playerul" << endl;
        cout << "       B. Afiseaza Echipe" << endl;
        cout << "       F. Citire playeri din fisier" << endl;
        cout << "       C. Adaugare player in echipa" << endl;
        cout << "       O. Organizare Meci" << endl;
        cout << "       X. Inchidere program\n" << endl;
        cout<<"===================================================================="<<endl;
        cin >> option;

        switch (toupper(option[0]))
        {
        case 'I':
        {
            // Player
            string Name, Age, Position, GoalScored;
            cout << "Introdu numele: ";
            cin >> Name;
            cout << "Introdu varsta: ";
            cin >> Age;
            cout << "Introdu pozitia: ";
            cin >> Position;
            cout << "Introdu nr de goluri: ";
            cin >> GoalScored;
            player = Player(Name, Age, Position, GoalScored);
            players.push_back(player); // adauga jucatorul la lista de jucatori
            break;
        }
        case 'E':
        {
            // Echipa 1
            cout << "ECHIPA 1............................." << endl;
            cout << "Introdu numele Echipei: ";
            cin.ignore();
            string name;
            getline(cin, name);

            cout << "Introdu numele antrenorului: ";
            string coach;
            getline(cin, coach);

            team1 = Team(name, coach);

            // Echipa 2
            cout << "ECHIPA 2............................." << endl;
            cout << "Introdu numele Echipei: ";
            string nume;
            getline(cin, nume);

            cout << "Introdu numele antrenorului: ";
            string antrenor;
            getline(cin, antrenor);

            team2 = Team(nume, antrenor);

            break;
        }



        case 'A':
        {
            player.ShowData();
            cout<<endl;
            break;
        }
        case 'B':
        {
            cout << "Care echipa doresti sa fie afisata" << endl;
            cout << "1. ";
            team1.ShowData();
            cout << endl;
            cout << "2. ";
            team2.ShowData();
            cout << endl;
            string apasa;
            cin >> apasa;
            if (apasa == "1")
            {
                cout << "==============   ECHIPA 1    ================" << endl;
                team1.ShowData();
                team1.ShowTeam();
            }
            else if (apasa == "2")
            {
                cout << "==============   ECHIPA 2    ================"<< endl;
                team2.ShowData();
                team2.ShowTeam();
            }
            break;
        }
        case 'F':
        {
            // Citirea jucătorilor din fișierul "jucatori.txt"
            players = CitireDinFisier("jucatori.txt", team1, team2);
            cout << "Jucatorii au fost cititi din fisierul 'jucatori.txt'." << endl;
            break;
        }
        case 'C':
        {
            cout << "In ce echipa vrei sa pui jucatorul?" << endl;
            cout << "1. ";
            team1.ShowData();
            cout << "2. ";
            team2.ShowData();
            string apas;
            cin >> apas;
            if (apas == "1")
            {
                team1.AddPlayer(player);
                cout << "PLAYER ADAUGAT!!" << endl;
            }
            else if (apas == "2")
            {
                team2.AddPlayer(player);
                cout << "PLAYER ADAUGAT!!" << endl;
            }
            break;
        }
        case 'O':
        {
            cout << "\n====================   INCEPE  MECIUL    ==================\n" << endl;
            Match match(team1, team2, "2023-03-18", "14:00");
            cout << "Meciul intre:\n";
            cout << team1.getName() << " - " << team2.getName() << " a inceput:\n" << endl;
            match.playMatch();
            cout << "\n====================   SFARSITUL MECIULUI    ==================\n" << endl;
            cout << "Detalii echipe:" << endl;
            match.ShowData();
            int team1Score = match.getTeam1Score();
            int team2Score = match.getTeam2Score();
            // Afisam scorul final
            cout << "Scor final: " << team1Score << " - " << team2Score << endl;
            break;
        }

        default:
        {
            cout << "Optiune inexistenta" << endl;
            break;
        }
        }
    }
    while (toupper(option[0]) != 'X');

    return 0;
}
