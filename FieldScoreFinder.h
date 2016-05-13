//
// Created by alperen on 23.04.2016.
//

#ifndef __FieldScoreFinder_H
#define __FieldScoreFinder_H


using namespace std;


class FieldScoreFinder {
    int rows, cols;
    char **tetris;

    int h0, h1, h2, h3, h4;

    float c0 = 100;
    float c1 = 20;
    float c2 = -100;
    float c3 = 10;
    float c4 = 10;
    float score;

    int findh0();

    int findh1();

    int findh2();

    int findh3();

    int findh4();

public:

    FieldScoreFinder() { }

    float findGradeForMatrix(char **tetris);

    void setRows(int rows_) { rows = rows_; }

    void setCols(int cols_) { cols = cols_; }
    //void setMatrix(char ** matrix){tetris=matrix;}


};

float FieldScoreFinder::findGradeForMatrix(char **tetris) {
    this->tetris = tetris;

    /*
    h0 = the number of holes in the playfield
    h1 = the altitude of the higher full cell in the playfield
    h2 = the number of full cells in the playfield
    h3 = the value of the higher slope in the playfield
    h4 = the roughness
    h5 = the number of full cells in the playfield weighted by their altitude
    */

    //new customPrint("kö");

    h0 = findh0();
    h1 = findh1();
    h2 = findh2();
    h3 = findh3();
    h4 = findh4();
    //h5=findh5();


    //score = c0 * h0 + c1 * h1 + c2 * h2 + c3 * h3 + c4 * h4 + c5 * h5;
    score = c0 * h0 + c1 * h1 + c2 * h2 + c3 * h3 + c4 * h4;
    //cout << "Total Score: " << score << endl;

    //new customPrint("Total Score: " +score);
    return score;

/*	for (int i = 0; i < rows; i++) { //arrayi yazdirma
		for (int j = 0; j < cols; j++)
			cout << tetris[i][j] << " ";
		cout << endl;
	}
*/

}

int FieldScoreFinder::findh0() {

    int h0 = 0;
    for (int i = 0; i < cols; i++) {
        int higest = 0;
        for (int j = 0; j < rows; j++) {
            if (tetris[j][i] != '0') {
                higest = j;
                j = rows;
            }
        }
        int spaces = 0;
        if (higest > 0) {
            for (int j = higest + 1; j < rows; j++) {
                if (tetris[j][i] == '0') {
                    spaces++;
                }
            }
        }
        h0 += spaces;
    }
    return h0;

}

int FieldScoreFinder::findh1() {
    int h1 = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!h1) {
                if (tetris[i][j] != '0') {
                    h1 = i;
                }
            }
        }
    }
    h1 = rows - h1;

    return h1;
}

int FieldScoreFinder::findh2() {

    int h2 = 0;
    for (int i = 0; i < rows; i++) {
        bool rowIsFull = true;
        for (int j = 0; j < cols; j++) {
            if (tetris[i][j] == '0') rowIsFull = false;
        }
        if (rowIsFull) h2++;
    }
    return h2;

}

int FieldScoreFinder::findh3() {
    int h3 = 0;
    int h3_temp = 0;
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            if (tetris[i][j] == '0') {
                if (j != 0 && j != cols - 1) {
                    if (tetris[i][j - 1] != '0' || tetris[i][j + 1] != '0') {
                        h3_temp++;
                    }
                }
                else if (j == 0) {
                    if (tetris[i][j + 1] != '0') {
                        h3_temp++;
                    }
                }
                else if (j == cols - 1) {
                    if (tetris[i][j - 1] != '0') {
                        h3_temp++;
                    }
                }

                if (h3_temp > h3)
                    h3 = h3_temp;
            }
            else {
                h3_temp = 0;
                break;
            }
        }
    }
    return h3;


}

int FieldScoreFinder::findh4() {
    int h4 = 0;
    for (int i = rows - 1; i > 1; i--) { //sol alttan baslayarak ilerliyoruz
        for (int j = 0; j < cols; j++) {
            if (tetris[i][j] != '0') { //dolu ise
                if (j != 0 &&
                    j != cols - 1) { //sol veya sag kose degil ise, bu durumda hem sag hem solunu kontrol edecegim
                    if (tetris[i][j - 1] == '0' && tetris[i - 1][j - 1] == '0' &&
                        tetris[i - 2][j - 1] == '0') { //solu, solunun bir ustu ve solunun iki ustu bos ise
                        h4++;
                    }

                    if (tetris[i][j + 1] == '0' && tetris[i - 1][j + 1] == '0' &&
                        tetris[i - 2][j + 1] == '0') { //sagi, saginin bir ustu ve saginin iki ustu bos ise
                        h4++;
                    }
                }
                else if (j == 0) { //sadece sagini kontrol et
                    if (tetris[i][j + 1] == '0' && tetris[i - 1][j + 1] == '0' &&
                        tetris[i - 2][j + 1] == '0') { //sagi, saginin bir ustu ve saginin iki ustu bos ise
                        h4++;
                    }

                }
                else if (j == cols - 1) { //sadece solunu kontrol et
                    if (tetris[i][j - 1] == '0' && tetris[i - 1][j - 1] == '0' &&
                        tetris[i - 2][j - 1] == '0') { //solu, solunun bir ustu ve solunun iki ustu bos ise
                        h4++;
                    }
                }
            }
        }
    }

    return h4;
}

#endif


