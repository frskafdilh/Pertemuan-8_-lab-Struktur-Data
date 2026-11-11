
#include<iostream>
#include<vector>
#include<string>
using namespace std;

const int TABLE_SIZE = 10;

class HashTable {
    private:
        vector <pair<long long, string>> table;
        vector <int> status;

        int hash1 (long long key) {
            return key % TABLE_SIZE;
        }

        int hash2 (long long key) {
            int step = 7 - (key % 7);

            while (step % 2 == 0 || step == 5) {
                step++;

                if (step > 7) {
                    step = 1;
                }
            }

            return step;
        }

    public:
        HashTable() {
            table.resize(TABLE_SIZE);
            status.resize(TABLE_SIZE, 0);
        }

        void insert (long long key, string value) {
            int index = hash1(key);
            int step = hash2(key);
            int deletedIndex = -1;

            for (int i = 0; i < TABLE_SIZE; i++) {
                if (status[index] == 1 && table[index].first == key) {
                    table[index].second = value;
                    cout << "Data berhasil diperbarui" << endl;
                    return;
                }

                if (status[index] == 2 && deletedIndex == -1) {
                    deletedIndex = index;
                }

                if (status[index] == 0) {
                    if (deletedIndex != -1) {
                        index = deletedIndex;
                    }

                    table[index] = make_pair(key, value);
                    status[index] = 1;
                    cout << "Data berhasil ditambahkan" << endl;
                    return;
                }

                index = (index + step) % TABLE_SIZE;
            }

            if (deletedIndex != -1) {
                table[deletedIndex] = make_pair(key, value);
                status[deletedIndex] = 1;
                cout << "Data berhasil ditambahkan" << endl;
            } else {
                cout << "Table penuh" << endl;
            }
        }

        void search (long long key) {
            int index = hash1(key);
            int step = hash2(key);

            for (int i = 0; i < TABLE_SIZE; i++) {
                if (status[index] == 0) {
                    break;
                }

                if (status[index] == 1 && table[index].first == key) {
                    cout << "Data ditemukan : " << table[index].second << endl;
                    return;
                }

                index = (index + step) % TABLE_SIZE;
            }

            cout << "Data tidak ditemukan" << endl;
        }

        void remove (long long key) {
            int index = hash1(key);
            int step = hash2(key);

            for (int i = 0; i < TABLE_SIZE; i++) {
                if (status[index] == 0) {
                    break;
                }

                if (status[index] == 1 && table[index].first == key) {
                    status[index] = 2;
                    cout << "Data berhasil dihapus" << endl;
                    return;
                }

                index = (index + step) % TABLE_SIZE;
            }

            cout << "Data tidak ditemukan" << endl;
        }

        void display() {
            for (int i = 0; i < TABLE_SIZE; i++) {
                cout << i << " : ";

                if (status[i] == 1) {
                    cout << table[i].first << " - " << table[i].second;
                } else if (status[i] == 2) {
                    cout << "DELETED";
                } else {
                    cout << "EMPTY";
                }

                cout << endl;
            }
        }
};

int main() {
    HashTable ht;

    int pilihan;
    long long nim;
    string nama;

    do {
        cout << "\nMenu Hash Table" << endl;
        cout << "1. Insert Data Mahasiswa" << endl;
        cout << "2. Search Data Mahasiswa" << endl;
        cout << "3. Remove Data Mahasiswa" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilih menu : ";
        cin >> pilihan;

        if (pilihan == 1) {
            cout << "Masukkan NIM : ";
            cin >> nim;

            cout << "Masukkan Nama : ";
            getline(cin >> ws, nama);

            ht.insert(nim, nama);
        } else if (pilihan == 2) {
            cout << "Masukkan NIM yang dicari : ";
            cin >> nim;

            ht.search(nim);
        } else if (pilihan == 3) {
            cout << "Masukkan NIM yang dihapus : ";
            cin >> nim;

            ht.remove(nim);
        } else if (pilihan == 4) {
            cout << "Program selesai." << endl;
        } else {
            cout << "Pilihan tidak valid" << endl;
        }

    } while (pilihan != 4);

    cout << "\nIsi Hash Table Akhir" << endl;
    ht.display();

    return 0;
}
