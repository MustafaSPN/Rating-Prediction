#include <iostream>
#include <fstream>
#include <string>
#include "class.h"
#include <cmath>
#include <ctime>



int main() {
    std::fstream inputFile;
    inputFile.open("train.csv", std::ios::in);
    if (!inputFile.is_open()) {
        std::cout << "File could not be opened." << std::endl;
    }
    std::string line;
    std::getline(inputFile, line);
    movieList *user = new movieList[35184];

    userList *movie = new userList[7331];

    while (!inputFile.eof()) {
        int a, b;
        double c;
        char k;
        inputFile >> a >> k >> b >> k >> c;

        user[a - 1].addMovie(b, c);
        movie[b - 1].add(a, c);

    }
    inputFile.close();

    double topTen[10][2];
    for (int i = 0; i < 10; ++i) {
        topTen[i][1] = 0;
    }


    for (int i = 0; i < 7331; ++i) {

        for (int j = 0; j < 10; ++j) {
            if (movie[i].count > topTen[j][1]) {
                int k = 9 - j;
                for (int l = 0; l < k; ++l) {
                    topTen[9 - l][1] = topTen[8 - l][1];
                    topTen[9 - l][0] = topTen[8 - l][0];
                }
                topTen[j][0] = i + 1;
                topTen[j][1] = movie[i].count;


                break;
            }
        }

    }
    std::cout << "Top Ten Movie: " << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << i + 1 << ".Movie ID: " << topTen[i][0] << " Rating Count: " << topTen[i][1] << std::endl;


    }
    for (int i = 0; i < 10; ++i) {
        topTen[i][1] = 0;
    }

    for (int i = 0; i < 35184; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (user[i].ratingCount > topTen[j][1]) {
                int k = 9 - j;
                for (int l = 0; l < k; ++l) {
                    topTen[9 - l][1] = topTen[8 - l][1];
                    topTen[9 - l][0] = topTen[8 - l][0];
                }
                topTen[j][0] = i + 1;
                topTen[j][1] = user[i].ratingCount;


                break;
            }
        }
    }
    std::cout << std::endl;
    std::cout << "Top Ten User: " << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << i + 1 << ".User ID: " << topTen[i][0] << " Rating Count: " << topTen[i][1] << std::endl;


    }


    inputFile.open("test.txt", std::ios::in);
    std::getline(inputFile, line);
    if (!inputFile.is_open()) {
        std::cout << "Test input file could not be opened." << std::endl;
    }

    std::ofstream outputFile;
    outputFile.open("prediction.txt", std::ios::out);
    if (!outputFile.is_open()) {
        std::cout << "OutputFile could not be opened." << std::endl;
    }

    while (!inputFile.eof()) {


        int a, b, c;
        char ml;

        inputFile >> a >> ml >> b >> ml >> c;

        double sum1 = 0, sum2 = 0;
        double count1 = 0, count2 = 0;
        double topSimilar[20][2];
        for (int j = 0; j < 20; ++j) {
            topSimilar[j][0] = 0;
            topSimilar[j][1] = 0;
        }
        for (int i = 0; i < 35184; i++) {


            if (user[i].ratingCount != 0) {
                if (user[i].movie[c - 1] != 0) {
                    double sim = user[b - 1].cosSimilarity(user[i]);
                    for (int j = 0; j < 20; ++j) {
                        if (sim > topSimilar[j][1]) {
                            int k = 19 - j;
                            for (int l = 0; l < k; ++l) {
                                topSimilar[19 - l][1] = topSimilar[18 - l][1];
                                topSimilar[19 - l][0] = topSimilar[18 - l][0];
                            }
                            topSimilar[j][0] = i;
                            topSimilar[j][1] = sim;
                            break;

                        }
                    }

                }
            }

        }
        for (int l = 0; l < 20; ++l) {
            int top = topSimilar[l][0];
            sum1 += pow(l + 1, -3) * user[top].movie[c - 1];
            count1 += pow(l + 1, -3);
        }
        for (int j = 0; j < 20; ++j) {
            topSimilar[j][0] = 0;
            topSimilar[j][1] = 0;
        }

        for (int i = 0; i < 7331; ++i) {
            if (movie[i].count != 0) {
                if (movie[i].userl[b - 1] != 0) {
                    double sim = movie[c - 1].cosSimilarity(movie[i]);
                    for (int j = 0; j < 20; ++j) {
                        if (sim > topSimilar[j][1]) {
                            int k = 19 - j;
                            for (int l = 0; l < k; ++l) {
                                topSimilar[19 - l][1] = topSimilar[18 - l][1];
                                topSimilar[19 - l][0] = topSimilar[18 - l][0];
                            }

                            topSimilar[j][0] = i;
                            topSimilar[j][1] = sim;
                            break;

                        }
                    }

                }
            }
        }


        for (int l = 0; l < 20; ++l) {
            int top = topSimilar[l][0];
            sum2 += pow(l + 1, -3) * movie[top].userl[b - 1];
            count2 += pow(l + 1, -3);
        }

        outputFile << a << "," << ((sum1 / count1) + (sum2 / count2)+(user[b-1].getAverage())+(movie[c-1].getAverage())) / 4 << std::endl;

    }
    std::cout << "All predictions were be done. Please check prediction.txt " << std::endl;

    std::cout << "Running time: " << (std::clock() / (int) CLOCKS_PER_SEC) / 60 << ":"
              << std::setfill('0') << std::setw(2) << (std::clock() / (int) CLOCKS_PER_SEC) % 60;

    return 1;
}