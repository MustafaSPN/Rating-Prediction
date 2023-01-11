//
// Created by Sepen on 1/1/2023.
//

#ifndef LASTTRY_CLASS_H
#define LASTTRY_CLASS_H

#include <cmath>
#include <iostream>

class movieList {
public:
    double movie[7331];
    int ratingCount;
    double totalRating;

    movieList() {
        for (int i = 0; i < 7331; i++) {
            this->movie[i] = 0;

        }
        this->ratingCount = 0;
        this->totalRating = 0;
    }

    void addMovie(const int &movieID, const double &rank) {

        this->movie[movieID - 1] = rank;
        this->ratingCount++;
        this->totalRating += rank;
    }


    double cosSimilarity(const movieList &id) {
        double upper = 0;
        double bottomF = 0;
        double bottomS = 0;
        for (int i = 0; i < 7331; i++) {

            if (id.ratingCount != 0 && (id.movie[i] != 0 || this->movie[i] != 0)) {
                upper += id.movie[i] * this->movie[i];
                bottomF += pow(id.movie[i], 2);
                bottomS += pow(this->movie[i], 2);
            }
        }


        return upper / (sqrt(bottomF) * sqrt(bottomS));

    }




    double getAverage() {
        return this->totalRating / this->ratingCount;

    }

};

class userList {
public:
    double userl[35184];
    int count;
    double totalRating;

    userList() {
        for (int i = 0; i < 35184; ++i) {
            userl[i] = 0;

        }
        this->count = 0;
        this->totalRating = 0;
    }

    void add(const int &userid, const double &rank) {

        this->userl[userid - 1] = rank;
        this->count++;
        this->totalRating += rank;

    }

    double cosSimilarity(const userList &id) {
        double upper = 0;
        double bottomF = 0;
        double bottomS = 0;
        double res;
        for (int i = 0; i < 35184; i++) {


            if (id.count != 0 && (id.userl[i] != 0 || this->userl[i] != 0)) {
                upper += id.userl[i] * this->userl[i];
                bottomF += pow(id.userl[i], 2);
                bottomS += pow(this->userl[i], 2);
            }
        }


        return upper / (sqrt(bottomF) * sqrt(bottomS));

    }


    double getAverage() {
        return this->totalRating / this->count;

    }
};

#endif //LASTTRY_CLASS_H
