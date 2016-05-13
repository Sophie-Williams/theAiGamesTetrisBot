//
// Created by alperen on 23.04.2016.
//

#ifndef __FinalPositionFinder_H
#define __FinalPositionFinder_H


#include "FieldScoreFinder.h"
#include <climits>

class FinalPositionFinder {
    int rows, cols;
    char **tetris;
    char shape;
    char nextShape;
    FieldScoreFinder fieldScoreFinder;

    void Set_Minimum_Cost(float *MinCost, float NewCost, int *MinX, int NewX, int *MinOrientation, int NewOrientation)
    {
        //<<"cost: "<<NewCost<<endl;
        if (NewCost < *MinCost)
        {
            *MinCost = NewCost;
            *MinX = NewX;
            *MinOrientation = NewOrientation;
        }
    }

    void Copy_Matrix(char **SourceMatrix, char **DestinationMatrix, int X, int Y)
    {
        for (int i = 0; i < Y; i++)
        {
            for (int j = 0; j < X; j++)
            {
                DestinationMatrix[i][j] = SourceMatrix[i][j];
            }
        }
    }

    int* findPosAndOrt(char **TetrisMatrix, char Shape,int degree);


public:

    int* getFinalPosition(){

        return computeFinalPosition();
    }

    int* computeFinalPosition();

    void setRows(int rows_){
        rows=rows_;
        fieldScoreFinder.setRows(rows_);
    }
    void setCols(int cols_){
        cols=cols_;
        fieldScoreFinder.setCols(cols_);
    }
    void setMatrix(char ** matrix){tetris=matrix;}
    void setShape(char shape_){shape=shape_;}
    void setNextShape(char shape_){nextShape=shape_;}
};


int* FinalPositionFinder::computeFinalPosition(){

    return findPosAndOrt(tetris, shape,1);

}

int* FinalPositionFinder::findPosAndOrt(char **TetrisMatrix, char Shape,int degree)
{
    int MinOrientation;
    int MinX;

    int i, j;

    int ShapeOrientationCount = 0;

    float MinCost = INT_MAX;
    float Cost=INT_MAX;


    char **TempTetris;
    TempTetris = new char*[rows];
    for (i = 0; i < rows; i++)
        TempTetris[i] = new char[cols];



    //region I


    if (Shape == 'I')
    {
        ShapeOrientationCount = 2;
        for (int ShapeOrientation = 0; ShapeOrientation < ShapeOrientationCount; ShapeOrientation++)
        {
            if (ShapeOrientation == 1)
            {
                for (i = 0; i < cols; i++)
                {
                    Copy_Matrix(TetrisMatrix, TempTetris, cols, rows);
                    for (j = 0; j < rows-3; j++)
                    {
                        if (TempTetris[j+3][i] == '1')
                        {
                            break;
                        }
                    }

                    if(j>0) j--;
                    TempTetris[j][i] = '1';
                    TempTetris[j+1][i] = '1';
                    TempTetris[j+2][i] = '1';
                    TempTetris[j+3][i] = '1';


                    Cost = fieldScoreFinder.findGradeForMatrix(TempTetris);
                    if(degree==1){
                        float secondDegreeCost= (float) (0.1 * findPosAndOrt(TempTetris, nextShape, 2)[0]);
                        Cost+=secondDegreeCost;
                    }
                    Set_Minimum_Cost(&MinCost, Cost, &MinX, i-2, &MinOrientation, ShapeOrientation); // +2 from rotation
                }
            }
            else if (ShapeOrientation == 0)
            {
                for (i = 0; i < cols-3; i++)
                {
                    Copy_Matrix(TetrisMatrix, TempTetris, cols, rows);
                    for (j = 0; j < rows; j++)
                    {
                        if (TempTetris[j][i] == '1' || TempTetris[j][i + 1] == '1' || TempTetris[j][i + 2] == '1' || TempTetris[j][i+3] == '1')
                        {
                            break;
                        }
                    }

                    if(j>0) j--;

                    TempTetris[j][i] = '1';
                    TempTetris[j][i+1] = '1';
                    TempTetris[j][i+2] = '1';
                    TempTetris[j][i+3] = '1';

                    Cost = fieldScoreFinder.findGradeForMatrix(TempTetris);
                    if(degree==1){
                        float secondDegreeCost= (float) (0.1 * findPosAndOrt(TempTetris, nextShape, 2)[0]);
                        Cost+=secondDegreeCost;
                    }

                    Set_Minimum_Cost(&MinCost, Cost, &MinX, i, &MinOrientation, ShapeOrientation); // +2 from rotation
                }

            }
        }
    }
        //endregion

        //region O
    else if (Shape == 'O')
    {
        for (i = 0; i < cols-1; i++)
        {
            Copy_Matrix(TetrisMatrix, TempTetris, cols, rows);
            for (j = 0; j < rows-1; j++)
            {
                if (TempTetris[j+1][i] == '1' || TempTetris[j+1][i + 1] == '1')
                {
                    break;
                }
            }

            if(j>0) j--;

            TempTetris[j][i] = '1';
            TempTetris[j][i+1] = '1';
            TempTetris[j+1][i] = '1';
            TempTetris[j+1][i+1] = '1';

            Cost = fieldScoreFinder.findGradeForMatrix(TempTetris);
            if(degree==1){
                int secondDegreeCost=findPosAndOrt(TempTetris,nextShape,2)[0];
                Cost+=secondDegreeCost;
            }
            Set_Minimum_Cost(&MinCost, Cost, &MinX, i, &MinOrientation, 0);

        }
    }
        //endregion

        //region S
    else if (Shape == 'S')
    {

        ShapeOrientationCount = 2;

        for (int ShapeOrientation = 0; ShapeOrientation < ShapeOrientationCount; ShapeOrientation++)
        {
            if (ShapeOrientation == 0)
            {
                for (i = 0; i < cols-2; i++)
                {
                    Copy_Matrix(TetrisMatrix, TempTetris, cols, rows);
                    for (j = 0; j < rows-1; j++)
                    {
                        if (TempTetris[j + 1][i] == '1' || TempTetris[j + 1][i + 1] == '1' || TempTetris[j][i+2] == '1')
                        {
                            break;
                        }
                    }

                    if(j>0) j--;
                    TempTetris[j][i+1] = '1';
                    TempTetris[j][i+2] = '1';
                    TempTetris[j+1][i] = '1';
                    TempTetris[j+1][i+1] = '1';

                    Cost = fieldScoreFinder.findGradeForMatrix(TempTetris);
                    if(degree==1){
                        int secondDegreeCost=findPosAndOrt(TempTetris,nextShape,2)[0];
                        Cost+=secondDegreeCost;
                    }
                    Set_Minimum_Cost(&MinCost, Cost, &MinX, i, &MinOrientation, ShapeOrientation);
                }
            }
            else if (ShapeOrientation == 1)
            {
                for (i = 0; i < cols-1; i++)
                {
                    Copy_Matrix(TetrisMatrix, TempTetris, cols, rows);
                    for (j = 0; j < rows-2; j++)
                    {
                        if (TempTetris[j+1][i] == '1' || TempTetris[j+2][i + 1] == '1')
                        {
                            break;
                        }
                    }

                    if(j>0) j--;
                    TempTetris[j][i] = '1';
                    TempTetris[j+1][i] = '1';
                    TempTetris[j+1][i+1] = '1';
                    TempTetris[j+2][i+1] = '1';

                    Cost = fieldScoreFinder.findGradeForMatrix(TempTetris);
                    if(degree==1){
                        int secondDegreeCost=findPosAndOrt(TempTetris,nextShape,2)[0];
                        Cost+=secondDegreeCost;
                    }
                    Set_Minimum_Cost(&MinCost, Cost, &MinX, i-1, &MinOrientation, ShapeOrientation);
                }

            }
        }


    }

        //endregion

        //region Z
    else if (Shape == 'Z')
    {

        ShapeOrientationCount = 2;

        for (int ShapeOrientation = 0; ShapeOrientation < ShapeOrientationCount; ShapeOrientation++)
        {
            if (ShapeOrientation == 0)
            {
                for (i = 0; i < cols-2; i++)
                {
                    Copy_Matrix(TetrisMatrix, TempTetris, cols, rows);
                    for (j = 0; j < rows-1; j++)
                    {
                        if (TempTetris[j][i] == '1' || TempTetris[j + 1][i + 1] == '1' || TempTetris[j+1][i + 2] == '1')
                        {
                            break;
                        }
                    }

                    if(j>0) j--;
                    TempTetris[j][i] = '1';
                    TempTetris[j][i + 1] = '1';
                    TempTetris[j + 1][i+1] = '1';
                    TempTetris[j + 1][i + 2] = '1';

                    Cost = fieldScoreFinder.findGradeForMatrix(TempTetris);
                    if(degree==1){
                        int secondDegreeCost=findPosAndOrt(TempTetris,nextShape,2)[0];
                        Cost+=secondDegreeCost;
                    }
                    Set_Minimum_Cost(&MinCost, Cost, &MinX, i, &MinOrientation, ShapeOrientation);
                }
            }
            else if (ShapeOrientation == 1)
            {
                for (i = 0; i < cols-1; i++)
                {
                    Copy_Matrix(TetrisMatrix, TempTetris, cols, rows);
                    for (j = 0; j < rows-2; j++)
                    {
                        if (TempTetris[j + 2][i] == '1' || TempTetris[j + 1][i + 1] == '1')
                        {
                            break;
                        }
                    }

                    if(j>0) j--;
                    TempTetris[j][i+1] = '1';
                    TempTetris[j + 1][i] = '1';
                    TempTetris[j + 1][i + 1] = '1';
                    TempTetris[j + 2][i] = '1';

                    Cost = fieldScoreFinder.findGradeForMatrix(TempTetris);
                    if(degree==1){
                        int secondDegreeCost=findPosAndOrt(TempTetris,nextShape,2)[0];
                        Cost+=secondDegreeCost;
                        //Cost = Insert_Tetris(TempTetris,nextShape,2)[0];
                    }
                    Set_Minimum_Cost(&MinCost, Cost, &MinX, i-1, &MinOrientation, ShapeOrientation);
                }

            }
        }


    }

        //endregion

        //region T
    else if (Shape == 'T')
    {
        ShapeOrientationCount = 4;

        for (int ShapeOrientation = 0; ShapeOrientation < ShapeOrientationCount; ShapeOrientation++)
        {
            if (ShapeOrientation == 2)
            {
                for (i = 0; i < cols-2; i++)
                {
                    Copy_Matrix(TetrisMatrix, TempTetris, cols, rows);
                    for (j = 0; j < rows-1; j++)
                    {
                        if (TempTetris[j][i] == '1' || TempTetris[j + 1][i + 1] == '1' || TempTetris[j][i+2] == '1')
                        {
                            break;
                        }
                    }

                    if(j>0) j--;


                    TempTetris[j][i] = '1';
                    TempTetris[j][i+1] = '1';
                    TempTetris[j][i+2] = '1';
                    TempTetris[j+1][i+1] = '1';

                    Cost = fieldScoreFinder.findGradeForMatrix(TempTetris);
                    if(degree==1){
                        int secondDegreeCost=findPosAndOrt(TempTetris,nextShape,2)[0];
                        Cost+=secondDegreeCost;
                    }
                    Set_Minimum_Cost(&MinCost, Cost, &MinX, i, &MinOrientation, ShapeOrientation);
                }
            }
            else if (ShapeOrientation == 3)
            {
                for (i = 0; i < cols-1; i++)
                {
                    Copy_Matrix(TetrisMatrix, TempTetris, cols, rows);
                    for (j = 0; j < rows-2; j++)
                    {
                        if (TempTetris[j+1][i] == '1' || TempTetris[j +2][i + 1] == '1')
                        {
                            break;
                        }
                    }

                    if(j>0) j--;
                    TempTetris[j+1][i] = '1';
                    TempTetris[j][i+1] = '1';
                    TempTetris[j+1][i+1] = '1';
                    TempTetris[j+2][i+1] = '1';

                    Cost = fieldScoreFinder.findGradeForMatrix(TempTetris);
                    if(degree==1){
                        int secondDegreeCost=findPosAndOrt(TempTetris,nextShape,2)[0];
                        Cost+=secondDegreeCost;
                    }
                    Set_Minimum_Cost(&MinCost, Cost, &MinX, i, &MinOrientation, ShapeOrientation);
                }

            }
            else if (ShapeOrientation == 0)
            {
                for (i = 0; i < cols-2; i++)
                {
                    Copy_Matrix(TetrisMatrix, TempTetris, cols, rows);
                    for (j = 0; j < rows-1; j++)
                    {
                        if (TempTetris[j+1][i] == '1' || TempTetris[j + 1][i + 1] == '1' || TempTetris[j + 1][i+2] == '1')
                        {
                            break;
                        }
                    }

                    if(j>0) j--;
                    TempTetris[j][i+1] = '1';
                    TempTetris[j+1][i] = '1';
                    TempTetris[j+1][i+1] = '1';
                    TempTetris[j+1][i+2] = '1';

                    Cost = fieldScoreFinder.findGradeForMatrix(TempTetris);
                    if(degree==1){
                        int secondDegreeCost=findPosAndOrt(TempTetris,nextShape,2)[0];
                        Cost+=secondDegreeCost;
                    }
                    Set_Minimum_Cost(&MinCost, Cost, &MinX, i, &MinOrientation, ShapeOrientation);
                }

            }
            else if (ShapeOrientation == 1)
            {
                for (i = 0; i < cols-1; i++)
                {
                    Copy_Matrix(TetrisMatrix, TempTetris, cols, rows);
                    for (j = 0; j < rows-2; j++)
                    {
                        if (TempTetris[j+2][i] == '1' || TempTetris[j + 1][i + 1] == '1')
                        {
                            break;
                        }
                    }

                    if(j>0) j--;
                    TempTetris[j][i] = '1';
                    TempTetris[j + 1][i] = '1';
                    TempTetris[j + 2][i] = '1';
                    TempTetris[j + 1][i + 1] = '1';

                    Cost = fieldScoreFinder.findGradeForMatrix(TempTetris);
                    if(degree==1){
                        int secondDegreeCost=findPosAndOrt(TempTetris,nextShape,2)[0];
                        Cost+=secondDegreeCost;
                    }
                    Set_Minimum_Cost(&MinCost, Cost, &MinX, i-1, &MinOrientation, ShapeOrientation); //+1 from rotation
                }

            }
        }
    }

        //endregion

        //region L
    else if (Shape == 'L')
    {
        ShapeOrientationCount = 4;

        for (int ShapeOrientation = 0; ShapeOrientation < ShapeOrientationCount; ShapeOrientation++)
        {
            if (ShapeOrientation == 1)
            {
                for (i = 0; i < cols-1; i++)
                {
                    Copy_Matrix(TetrisMatrix, TempTetris, cols, rows);
                    for (j = 0; j < rows-2; j++)
                    {
                        if (TempTetris[j+2][i] == '1' || TempTetris[j + 2][i + 1] == '1')
                        {
                            break;
                        }
                    }

                    if(j>0) j--;
                    TempTetris[j][i] = '1';
                    TempTetris[j + 1][i] = '1';
                    TempTetris[j + 2][i] = '1';
                    TempTetris[j + 2][i + 1] = '1';

                    Cost = fieldScoreFinder.findGradeForMatrix(TempTetris);
                    if(degree==1){
                        int secondDegreeCost=findPosAndOrt(TempTetris,nextShape,2)[0];
                        Cost+=secondDegreeCost;
                    }
                    Set_Minimum_Cost(&MinCost, Cost, &MinX, i-1, &MinOrientation, ShapeOrientation); //+1 from rot
                }
            }
            else if (ShapeOrientation == 2)
            {
                for (i = 0; i < cols-2; i++)
                {
                    Copy_Matrix(TetrisMatrix, TempTetris, cols, rows);
                    for (j = 0; j < rows-1; j++)
                    {
                        if (TempTetris[j + 1][i] == '1' || TempTetris[j][i + 1] == '1' || TempTetris[j][i + 2] == '1')
                        {
                            break;
                        }
                    }

                    if(j>0) j--;
                    TempTetris[j][i] = '1';
                    TempTetris[j + 1][i] = '1';
                    TempTetris[j][i + 1] = '1';
                    TempTetris[j][i + 2] = '1';

                    Cost = fieldScoreFinder.findGradeForMatrix(TempTetris);
                    if(degree==1){
                        int secondDegreeCost=findPosAndOrt(TempTetris,nextShape,2)[0];
                        Cost+=secondDegreeCost;
                    }
                    Set_Minimum_Cost(&MinCost, Cost, &MinX, i, &MinOrientation, ShapeOrientation);
                }

            }
            else if (ShapeOrientation == 3)
            {
                for (i = 0; i < cols-1; i++)
                {
                    Copy_Matrix(TetrisMatrix, TempTetris, cols, rows);
                    for (j = 0; j < rows-2; j++)
                    {
                        if (TempTetris[j][i] == '1' || TempTetris[j + 2][i + 1] == '1')
                        {
                            break;
                        }
                    }

                    if(j>0) j--;
                    TempTetris[j][i] = '1';
                    TempTetris[j][i+1] = '1';
                    TempTetris[j + 1][i + 1] = '1';
                    TempTetris[j + 2][i + 1] = '1';

                    Cost = fieldScoreFinder.findGradeForMatrix(TempTetris);
                    if(degree==1){
                        int secondDegreeCost=findPosAndOrt(TempTetris,nextShape,2)[0];
                        Cost+=secondDegreeCost;
                        //Cost = Insert_Tetris(TempTetris,nextShape,2)[0];
                    }
                    Set_Minimum_Cost(&MinCost, Cost, &MinX, i, &MinOrientation, ShapeOrientation);
                    //Print_Matrix_To_File(TempTetris);
                }

            }
            else if (ShapeOrientation == 0)
            {
                for (i = 0; i < cols-2; i++)
                {
                    Copy_Matrix(TetrisMatrix, TempTetris, cols, rows);
                    for (j = 0; j < rows-1; j++)
                    {
                        if (TempTetris[j + 1][i] == '1' || TempTetris[j + 1][i + 1] == '1' || TempTetris[j + 1][i + 2] == '1')
                        {
                            break;
                        }
                    }

                    if(j>0) j--;
                    TempTetris[j + 1][i] = '1';
                    TempTetris[j + 1][i + 1] = '1';
                    TempTetris[j + 1][i + 2] = '1';
                    TempTetris[j][i + 2] = '1';

                    Cost = fieldScoreFinder.findGradeForMatrix(TempTetris);
                    if(degree==1){
                        int secondDegreeCost=findPosAndOrt(TempTetris,nextShape,2)[0];
                        Cost+=secondDegreeCost;
                    }
                    Set_Minimum_Cost(&MinCost, Cost, &MinX, i, &MinOrientation, ShapeOrientation);
                }


            }
        }
    }
        // endregion

        //region J
    else if (Shape == 'J')
    {
        ShapeOrientationCount = 4;

        for (int ShapeOrientation = 0; ShapeOrientation < ShapeOrientationCount; ShapeOrientation++)
        {
            if (ShapeOrientation == 3)
            {
                for (i = 0; i < cols-1; i++)
                {
                    Copy_Matrix(TetrisMatrix, TempTetris, cols, rows);
                    for (j = 0; j < rows-2; j++)
                    {
                        if (TempTetris[j + 2][i] == '1' || TempTetris[j + 2][i + 1] == '1')
                        {
                            break;
                        }
                    }

                    if(j>0) j--;
                    TempTetris[j][i+1] = '1';
                    TempTetris[j+1][i+1] = '1';
                    TempTetris[j+2][i+1] = '1';
                    TempTetris[j + 2][i] = '1';

                    Cost = fieldScoreFinder.findGradeForMatrix(TempTetris);
                    if(degree==1){
                        int secondDegreeCost=findPosAndOrt(TempTetris,nextShape,2)[0];
                        Cost+=secondDegreeCost;
                    }
                    Set_Minimum_Cost(&MinCost, Cost, &MinX, i, &MinOrientation, ShapeOrientation);
                }
            }
            else if (ShapeOrientation == 0)
            {
                for (i = 0; i < cols-2; i++)
                {
                    Copy_Matrix(TetrisMatrix, TempTetris, cols, rows);
                    for (j = 0; j < rows-1; j++)
                    {
                        if (TempTetris[j + 1][i] == '1' || TempTetris[j + 1][i + 1] == '1' || TempTetris[j + 1][i + 2] == '1')
                        {
                            break;
                        }
                    }

                    if(j>0) j--;
                    TempTetris[j][i] = '1';
                    TempTetris[j + 1][i] = '1';
                    TempTetris[j + 1][i + 1] = '1';
                    TempTetris[j+1][i + 2] = '1';

                    Cost = fieldScoreFinder.findGradeForMatrix(TempTetris);
                    if(degree==1){
                        int secondDegreeCost=findPosAndOrt(TempTetris,nextShape,2)[0];
                        Cost+=secondDegreeCost;
                    }
                    Set_Minimum_Cost(&MinCost, Cost, &MinX, i, &MinOrientation, ShapeOrientation);
                }

            }
            else if (ShapeOrientation == 1)
            {
                for (i = 0; i < cols-1; i++)
                {
                    Copy_Matrix(TetrisMatrix, TempTetris, cols, rows);
                    for (j = 0; j < rows-2; j++)
                    {
                        if (TempTetris[j+2][i] == '1' || TempTetris[j][i + 1] == '1')
                        {
                            break;
                        }
                    }

                    if(j>0) j--;
                    TempTetris[j][i] = '1';
                    TempTetris[j][i + 1] = '1';
                    TempTetris[j + 1][i] = '1';
                    TempTetris[j + 2][i] = '1';

                    Cost = fieldScoreFinder.findGradeForMatrix(TempTetris);
                    if(degree==1){
                        int secondDegreeCost=findPosAndOrt(TempTetris,nextShape,2)[0];
                        Cost+=secondDegreeCost;
                    }
                    Set_Minimum_Cost(&MinCost, Cost, &MinX, i-1, &MinOrientation, ShapeOrientation);
                }

            }
            else if (ShapeOrientation == 2)
            {
                for (i = 0; i < cols-2; i++)
                {
                    Copy_Matrix(TetrisMatrix, TempTetris, cols, rows);
                    for (j = 0; j < rows-1; j++)
                    {
                        if (TempTetris[j][i] == '1' || TempTetris[j][i + 1] == '1' || TempTetris[j+1][i + 2] == '1')
                        {
                            break;
                        }
                    }

                    if(j>0) j--;
                    TempTetris[j][i] = '1';
                    TempTetris[j][i+1] = '1';
                    TempTetris[j][i + 2] = '1';
                    TempTetris[j+1][i + 2] = '1';

                    Cost = fieldScoreFinder.findGradeForMatrix(TempTetris);
                    if(degree==1){
                        int secondDegreeCost=findPosAndOrt(TempTetris,nextShape,2)[0];
                        Cost+=secondDegreeCost;
                    }
                    Set_Minimum_Cost(&MinCost, Cost, &MinX, i, &MinOrientation, ShapeOrientation);
                }

            }
        }
    }
    //endregion



    for (i = 0; i < rows; i++)
        delete[] TempTetris[i];

    delete[] TempTetris;

    int *result=new int[2];
    result[0]=MinX;
    result[1]=MinOrientation;
    return result;

}



#endif