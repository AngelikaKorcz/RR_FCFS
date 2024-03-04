#include <iostream>
#include <fstream>
using namespace std;

void FCFS()
{
    int current_time = 0;
    int wait_time = 0;
    int turnaround_time = 0;
    int n, arrival_time[1000], burst_time[1000];

    cout << "Liczba procesow: ";
    cin >> n;


    for (int i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "]:";
        cin >> burst_time[i];
        arrival_time[i] = 0;

        // cout << "Kolejnosc przybycia " << i + 1 << " procesu: ";                      
         //cin >> arrival_time[i];
    }


    for (int i = 0; i < n; i++) {
        if (current_time < arrival_time[i])         //current_time=czas biezacy
        {
            current_time = arrival_time[i];         //proces nie przybyl, wiec ustawiamy czas biezacy na czas przybycia 
        }
        wait_time += current_time - arrival_time[i];        //czas oczekiwania zwiekszamy o roznice czasu biezacego i czasu przybycia
        turnaround_time += current_time + burst_time[i] - arrival_time[i];      //czas trwania procesu
        current_time += burst_time[i];                                      //ustawiamy biezacy czas
    }


    cout << "\t\t FCFS" << endl;


    cout << "Process\tburst time\tarrival time\n";
    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << "\t\t" << burst_time[i] << "\t\t" << arrival_time[i] << "\t\t" << endl;
    }


    float avg_wait_time = (float)wait_time / n;         //liczymy sredni czas  oczekiwania
    float avg_turnaround_time = (float)turnaround_time / n;  // sredni czas trwania

    cout << "average waiting time: " << avg_wait_time << endl;
    cout << "average turnaround time: " << avg_turnaround_time << endl;

    //zapisywanie do pliku
    ofstream zapis;
    zapis.open("FCFS_wyniki.txt", ios::app);
    zapis << "Process\tburst time\tarrival time\n";
    for (int i = 0; i < n; i++)
    {
        zapis << i + 1 << "\t\t" << burst_time[i] << "\t\t" << arrival_time[i] << "\t\t" << endl;
    }
    zapis << "average waiting time: " << avg_wait_time << endl;
    zapis << "average turnaround time: " << avg_turnaround_time << endl;
    zapis.close();
}


void roundRobin()
{

    int burst_time[100];
    int waiting_time[100];
    int remaining_time[100];
    int turnaround_time[100];
    int QUANTUM, t = 0, n;

    cout << "Podaj liczbe procesow: ";
    cin >> n;

    cout << "Podaj czas QUANTUM: ";
    cin >> QUANTUM;


    cout << "Podaj czas trwania procesow (burst time): " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "]:";
        cin >> burst_time[i];
    }

    for (int i = 0; i < n; i++)             // Inicjalizowanie pozostałego czasu do trwania procesów, wszystke procesy zaczynaja prace od poczatku
    {
        remaining_time[i] = burst_time[i];
    }


    while (true) {
        bool done = true;
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0)
            {
                done = false;
                if (remaining_time[i] > QUANTUM) // Jeśli pozostały czas jest większy niż quantum
                {
                    t += QUANTUM;                        // dodanie quantum do aktualnego czasu
                    remaining_time[i] -= QUANTUM;      // odejmowanie quantum od pozostałego czasu
                }
                else
                {
                    t = t + remaining_time[i];                  // dodanie pozostałego czasu do aktualnego czasu
                    waiting_time[i] = t - burst_time[i];    // Czas oczekiwania to różnica między aktualnym czasem a czasem trwania procesu
                    remaining_time[i] = 0;                  //ustawienie pozostałego czasu na 0, ponieważ proces jest zakończony
                }
            }
        }
        if (done) break;           // Jeśli wszystkie procesy zakończone, zakończyć pętlę
    }

    double sum_waiting_time = 0;
    double sum_turnaround_time = 0;
    for (int i = 0; i < n; i++)                 //obliczamy czas realizacji procesu oraz sume czasu oczekiwania
    {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
        sum_waiting_time += waiting_time[i];
        sum_turnaround_time += turnaround_time[i];
    }

    double average_waiting_time = sum_waiting_time / n;                 //liczymy średni czas oczekiwania
    double average_turnaround_time = sum_turnaround_time / n;           //liczymy średni czas realizacji procesu

    cout << "\t\t Round Robin" << endl;


    cout << "Proces\tburst time\twaitting time\tturnaround time\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t\t" << burst_time[i] << "\t\t" << waiting_time[i] << "\t\t" << turnaround_time[i] << endl;
    }
    cout << "Average Waiting Time: " << average_waiting_time << endl;
    cout << "Average Turnaround Time: " << average_turnaround_time << endl;



    //zapisywanie do pliku
    ofstream zapis;
    zapis.open("RR_wyniki.txt", ios::app);
    zapis << "Quantum: " << QUANTUM << endl;
    zapis << "Proces\tburst time\twaitting time\tturnaround time\n";
    for (int i = 0; i < n; i++)
    {
        zapis << i + 1 << "\t\t" << burst_time[i] << "\t\t" << waiting_time[i] << "\t\t" << turnaround_time[i] << endl;
    }
    zapis << "average waiting time: " << average_waiting_time << endl;
    zapis << "average turnaround time: " << average_turnaround_time << endl;
    zapis.close();
}






int main()
{
    int check;
    cout << "Ktory algorytm chcesz wywolac? 1-FCFS 2-Round Robin ";
    cin >> check;


    switch (check)
    {
    case 1:
        FCFS();
        break;
    case 2:
        roundRobin();
        break;
    }

}

