#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;


// Ad Soyad: HAVVA ÇIRPAÇ
// Proje: Telefon ve Uyku Analiz Sistemi


#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"



class Person {

protected:
    string name;

public:

    Person(string n) {
        name = n;
    }

    string getName() const {
        return name;
    }
};



class SleepRecord : public Person {

private:

    double phoneHours;
    double sleepHours;
    int quality;

public:

    SleepRecord(string n, double p, double s, int q)
        : Person(n) {

        phoneHours = p;
        sleepHours = s;
        quality = q;
    }

    double getPhoneHours() const {
        return phoneHours;
    }

    double getSleepHours() const {
        return sleepHours;
    }

    int getQuality() const {
        return quality;
    }

    string getStatus() const {

        if (sleepHours < 5)
            return "TEHLIKELI";

        else if (sleepHours < 7)
            return "YETERSIZ";

        else
            return "SAGLIKLI";
    }

    string getColor() const {

        if (sleepHours < 5)
            return RED;

        else if (sleepHours < 7)
            return YELLOW;

        else
            return GREEN;
    }

    void display() const {

        cout << getColor();

        cout << left << setw(12) << name
            << " Telefon: " << setw(5) << phoneHours
            << " Uyku: " << setw(5) << sleepHours
            << " Kalite: " << setw(3) << quality
            << " Durum: " << getStatus()
            << endl;

        cout << RESET;
    }
};



class SleepAnalyzer {

private:

    vector<SleepRecord> records;
    map<int, int> qualityFreq;

public:

    void addRecord(const SleepRecord& r) {

        records.push_back(r);

        cout << GREEN;
        cout << "\nKayit basariyla eklendi.\n";
        cout << RESET;
    }

    void showAll() const {

        if (records.empty()) {

            cout << RED;
            cout << "\nKayit yok!\n";
            cout << RESET;

            return;
        }

        cout << CYAN;
        cout << "\n";
        cout << "\n";
        cout << "\n";
        cout << RESET;

        for (const auto& r : records) {
            r.display();
        }
    }

    double averageSleep() const {

        if (records.empty())
            return 0;

        double total = 0;

        for (const auto& r : records) {
            total += r.getSleepHours();
        }

        return total / records.size();
    }

    double averagePhoneUsage() const {

        if (records.empty())
            return 0;

        double total = 0;

        for (const auto& r : records) {
            total += r.getPhoneHours();
        }

        return total / records.size();
    }

    double maxSleep() const {

        if (records.empty())
            return 0;

        double maxValue = records[0].getSleepHours();

        for (const auto& r : records) {

            if (r.getSleepHours() > maxValue)
                maxValue = r.getSleepHours();
        }

        return maxValue;
    }

    double minSleep() const {

        if (records.empty())
            return 0;

        double minValue = records[0].getSleepHours();

        for (const auto& r : records) {

            if (r.getSleepHours() < minValue)
                minValue = r.getSleepHours();
        }

        return minValue;
    }

    
    void removeUnhealthy() {

        vector<SleepRecord> temp;

        for (const auto& r : records) {

            if (r.getSleepHours() >= 5) {
                temp.push_back(r);
            }
        }

        records = temp;

        cout << YELLOW;
        cout << "\n5 saat altý uyuyanlar silindi.\n";
        cout << RESET;
    }

    
    void sortByQuality() {

        sort(records.begin(), records.end(),

            [](SleepRecord a, SleepRecord b) {

                return a.getQuality() > b.getQuality();
            });

        cout << GREEN;
        cout << "\nKayitlar kaliteye gore siralandi.\n";
        cout << RESET;
    }

    
    void calculateFrequency() {

        qualityFreq.clear();

        for (const auto& r : records) {

            qualityFreq[r.getQuality()]++;
        }
    }

    
    void cumulativeFrequency() {

        if (records.empty()) {

            cout << RED;
            cout << "\nVeri yok!\n";
            cout << RESET;

            return;
        }

        calculateFrequency();

        int total = 0;

        cout << MAGENTA;
        cout << "\n\n";
        cout << "\n";
        cout << "\n";
        cout << RESET;

        for (auto p : qualityFreq) {

            total += p.second;

            cout << BLUE
                << "Kalite "
                << p.first
                << " -> "
                << total
                << RESET
                << endl;
        }
    }

    
    void bestSleeper() {

        if (records.empty()) {

            cout << RED;
            cout << "\nKayit yok!\n";
            cout << RESET;

            return;
        }

        SleepRecord best = records[0];

        for (const auto& r : records) {

            if (r.getQuality() > best.getQuality()) {
                best = r;
            }
        }

        cout << GREEN;
        cout << "\n\n";
        cout << "\n";
        cout << "\n";
        cout << RESET;

        best.display();
    }

   
    void riskAnalysis() const {

        if (records.empty()) {

            cout << RED;
            cout << "\nVeri yok!\n";
            cout << RESET;

            return;
        }

        int risky = 0;

        for (const auto& r : records) {

            if (r.getSleepHours() < 5)
                risky++;
        }

        cout << MAGENTA;
        cout << "\n\n";
        cout << "\n";
        cout << "\n";
        cout << RESET;

        if (risky == 0) {

            cout << GREEN;
            cout << "Risk seviyesi dusuk.\n";
        }

        else if (risky < 3) {

            cout << YELLOW;
            cout << "Orta seviye risk var.\n";
        }

        else {

            cout << RED;
            cout << "Yuksek risk tespit edildi!\n";
        }

        cout << RESET;
    }

    
    void saveToFile(string filename) {

        ofstream file(filename);

        file << "===== UYKU RAPORU =====\n\n";

        for (const auto& r : records) {

            file << r.getName()
                << " | Telefon: " << r.getPhoneHours()
                << " | Uyku: " << r.getSleepHours()
                << " | Kalite: " << r.getQuality()
                << " | Durum: " << r.getStatus()
                << endl;
        }

        file << "\nOrtalama Uyku: "
            << averageSleep()
            << endl;

        file << "Ortalama Telefon Kullanimi: "
            << averagePhoneUsage()
            << endl;

        file << "En Fazla Uyku: "
            << maxSleep()
            << endl;

        file << "En Az Uyku: "
            << minSleep()
            << endl;

        file.close();

        cout << GREEN;
        cout << "\nRapor dosyaya kaydedildi.\n";
        cout << RESET;
    }
};



int main() {

    SleepAnalyzer analyzer;

    int secim;

    cout << CYAN;
    cout << "=========================================\n";
    cout << "   TELEFON VE UYKU ANALIZ SISTEMI\n";
    cout << "=========================================\n";
    cout << RESET;

    do {

        cout << BLUE;
        cout << "\n============= MENU =============\n";
        cout << RESET;

        cout << "1- Kayit Ekle\n";
        cout << "2- Kayitlari Goster\n";
        cout << "3- Istatistikler\n";
        cout << "4- Sagliksizlari Sil\n";
        cout << "5- Kaliteye Gore Sirala\n";
        cout << "6- Yigilmalý Frekans\n";
        cout << "7- En Saglikli Kisi\n";
        cout << "8- Risk Analizi\n";
        cout << "9- Dosyaya Kaydet\n";
        cout << "0- Cikis\n";

        cout << YELLOW;
        cout << "\nSecim: ";
        cout << RESET;

        cin >> secim;

        if (secim == 1) {

            string name;
            double phone;
            double sleep;
            int quality;

            cout << CYAN;
            cout << "\nIsim: ";
            cout << RESET;
            cin >> name;

            cout << CYAN;
            cout << "Gunluk telefon kullanimi(saat): ";
            cout << RESET;
            cin >> phone;

            cout << CYAN;
            cout << "Gunluk uyku(saat): ";
            cout << RESET;
            cin >> sleep;

            cout << CYAN;
            cout << "Uyku kalitesi(1-10): ";
            cout << RESET;
            cin >> quality;

            analyzer.addRecord(
                SleepRecord(name, phone, sleep, quality)
            );
        }

        else if (secim == 2) {

            analyzer.showAll();
        }

        else if (secim == 3) {

            cout << MAGENTA;
            cout << "\n============= ISTATISTIKLER =============\n";
            cout << RESET;

            cout << GREEN
                << "Ortalama uyku: "
                << analyzer.averageSleep()
                << RESET
                << endl;

            cout << GREEN
                << "Ortalama telefon kullanimi: "
                << analyzer.averagePhoneUsage()
                << RESET
                << endl;

            cout << GREEN
                << "En fazla uyku: "
                << analyzer.maxSleep()
                << RESET
                << endl;

            cout << GREEN
                << "En az uyku: "
                << analyzer.minSleep()
                << RESET
                << endl;
        }

        else if (secim == 4) {

            analyzer.removeUnhealthy();
        }

        else if (secim == 5) {

            analyzer.sortByQuality();
        }

        else if (secim == 6) {

            analyzer.cumulativeFrequency();
        }

        else if (secim == 7) {

            analyzer.bestSleeper();
        }

        else if (secim == 8) {

            analyzer.riskAnalysis();
        }

        else if (secim == 9) {

            analyzer.saveToFile("uyku_raporu.txt");
        }

    } while (secim != 0);

    cout << RED;
    cout << "\nProgram sonlandi.\n";
    cout << RESET;

    return 0;
}