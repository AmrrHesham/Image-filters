#include<iostream>
#include<fstream>
#include<cstring>
#include<cmath>
#include<stdlib.h>
#include"bmplib.cpp"

using namespace std;

// Images which will be used in the program
// Using 2D arrays for GreyScale images
unsigned char image[SIZE][SIZE];  // to load first photo.
unsigned char image2[SIZE][SIZE]; // to load second photo if we merge two photos. and we use it in another function.
unsigned char Q1[SIZE/2][SIZE/2]; // for shuffle Q1
unsigned char Q2[SIZE/2][SIZE/2]; // Q2
unsigned char Q3[SIZE/2][SIZE/2]; // Q3
unsigned char Q4[SIZE/2][SIZE/2]; // Q4

// Prototypes
void loadImage();
void saveImage();
void mergeImages();
void lightenOrDarkenImage();
void shrinkImage();
void blurImage();
void enlargeImage();
void rotateImage();
void flipVertically();
void flipHorizontally();
void mirrorLeftHalf();
void mirrorUpperHalf();
void detectEdges();
void blackAndWhite();
void mirrorLowerHalf();
void mirrorRightHalf();
void invertImage();
void insertQuarter(unsigned char quarter[SIZE/2][SIZE/2],int row,int column);
void makeQuarter1();
void makeQuarter2();
void makeQuarter3();
void makeQuarter4();
void shuffleImage();

// Get users choice to see which filter he wants to try
int main()
{
    char ans;
    cout << "Welcome User" << endl;
    cout << "Which filter would you like to try" << endl;
    cout << "1. Black & White Filter\n2. Invert Filter\n3. Merge Filter\n4. Flip Image\n5. Darken and Lighten Image\n6. Rotate Image\n";
    cout << "7. Detect Image Edges\n8. Enlarge Image\n9. Shrink Image\na. Mirror 1/2 Image\nb. Shuffle Image\nc. Blur Image\n0. Exit" << endl;
    cin >> ans;
    if(ans == '1')
    {
        loadImage();
        blackAndWhite();
        saveImage();
        main();
    }
    else if(ans == '2')
    {
        loadImage();
        invertImage();
        saveImage();
        main();
    }
    else if(ans == '3')
    {
        loadImage();
        mergeImages();
        saveImage();
        main();
    }
    else if(ans == '4')
    {
        int ans2;
        cout << "1. Horizontal Flip\n2. Vertical Flip" << endl;
        cin >> ans2;
        if(ans2 == 1)
        {
            loadImage();
            flipHorizontally();
            saveImage();
            main();
        }
        else if(ans2 == 2)
        {
            loadImage();
            flipVertically();
            saveImage();
            main();
        }
        else
        {
            cout << "Invalid input" << endl;
            main();
        }
    }
    else if(ans == '5')
    {
        loadImage();
        lightenOrDarkenImage();
        saveImage();
        main();
    }
    else if(ans == '6')
    {
        loadImage();
        rotateImage();
        saveImage();
        main();
    }
    else if(ans == '7')
    {
        loadImage();
        detectEdges();
        saveImage();
        main();
    }
    else if(ans == '8')
    {
        loadImage();
        enlargeImage();
        saveImage();
        main();
    }
    else if(ans == '9')
    {
        loadImage();
        shrinkImage();
        saveImage();
        main();
    }
    else if(ans == 'a')
    {
        int ans2;
        cout << "1. Right Half\n2. Left Half\n3. Upper Half\n4. Lower Half" << endl;
        cin >> ans2;
        if(ans2 == 1)
        {
            loadImage();
            mirrorRightHalf();
            saveImage();
            main();
        }
        else if(ans2 == 2)
        {
            loadImage();
            mirrorLeftHalf();
            saveImage();
            main();
        }
        else if(ans == 3)
        {
            loadImage();
            mirrorUpperHalf();
            saveImage();
            main();
        }
        else if(ans == 4)
        {
            loadImage();
            mirrorLowerHalf();
            saveImage();
            main();
        }
        else
        {
            cout << "Invalid input" << endl;
            main();
        }
    }
    else if(ans == 'b')
    {
        loadImage();
        shuffleImage();
        saveImage();
        main();
    }
    else if(ans == 'c')
    {
        loadImage();
        blurImage();
        saveImage();
        main();
    }
    else if(ans == '0')
    {
        cout << "Thank you for using the filters" << endl;
        exit(0);
    }
    else
    {
        cout << "Invalid input" << endl;
        main();
    }
}

// Load image which the user wants to filter
void loadImage(){ 
    char fileOfImage[20];
    cout << "Enter name of the image you want to filter: ";
    cin >> fileOfImage;

    strcat (fileOfImage, ".bmp");
    readGSBMP(fileOfImage, image);

}

// Load second image from user if needed
void loadSecondImage(){
    char fileOfImage[20];
    cout << "Enter second image name: ";
    cin >> fileOfImage;

    strcat (fileOfImage, ".bmp");
    readGSBMP(fileOfImage, image2);
}

// Save the edited image with the user's name choice
void saveImage(){
    char fileOfImage[20];
    cout << "plz enter the target file name: ";
    cin >> fileOfImage;

    strcat (fileOfImage, ".bmp");
    writeGSBMP(fileOfImage, image); 
}

// Function that merge two images together
void mergeImages() {
    loadSecondImage();
    for (int i = 0; i < SIZE; i++) // This nested for loop add the average color of the two images together
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = ((image[i][j] + image2[i][j]) / 2);
        }
    }
}

// Function that darken or lighten the image
void lightenOrDarkenImage(){
    int answer;
    cout << "do you want to do lighten or darken: \n1-darken\n2-lighten " << endl;
    cin >> answer;

    if (answer == 1){
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i][j] = (image[i][j] / 2);
            }
        }
    }
    else if (answer == 2){
       for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if (image[i][j] < 140)
                {
                    image[i][j] = 100 + image[i][j];
                }
                else if (image[i][j] > 140)
                {
                    image[i][j] = 255;
                }
                else if (image[i][j] == 0)
                {
                    image[i][j] = 100;
                }
            }
        }
    }
    else{
        cout << "Invalid Input!";
        lightenOrDarkenImage();
    }
}

// Function that shrink image to: 1/2 or 1/3 or 1/4
void shrinkImage(){ 
    unsigned char image2[SIZE][SIZE];
    int answer;
    cout << "1. Half.\n2. Third.\n3. Quarter.\n"; //ask user?
    cin >> answer;
    if (answer == 1){ //if user enter 1, do (1/2)shrink.
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++){
                image[i/2][j/2] = (image[i][j] + image[i+1][j] + image[i][j+1] + image[i+1][j+1]) / 4;
            }
        }
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++){
                if (i < 127 && j < 127){
                    image2[i][j] = image[i][j];
                }
                else{
                    image2[i][j] = 255;
                }
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i][j] = image2[i][j];
            }
        }
    }
    else if (answer == 2){ //if user enter 1, do (1/3)shrink.
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++){
                image[i/3][j/3] = (image[i][j] + image[i+1][j] + image[i+2][j] + image[i][j+1] + image[i][j+2] + image[i+2][j+2] + 
                                   image[i+1][j+2] + image[i+2][j+1] + image[i+1][j+1]) / 9;
            }
        }
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++){
                if (i < 85 && j < 85){
                    image2[i][j] = image[i][j];
                }
                else{
                    image2[i][j] = 255;
                }
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i][j] = image2[i][j];
            }
        }
    }
    else if (answer == 3){ //if user enter 1, do (1/4)shrink.
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++){
                image[i/4][j/4] = (image[i][j] + image[i+1][j] + image[i+2][j] + image[i][j+1] + image[i][j+2] + image[i+2][j+2] + 
                                   image[i+1][j+2] + image[i+2][j+1] + image[i+1][j+1] + image[i+3][j] + image[i][j+3] + image[i+3][j+3] + 
                                   image[i+1][j+3] + image[i+2][j+3] + image[i+3][j+1] + image[i+3][j+2]) / 16;
            }
        }
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++){
                if (i < 64 && j < 64){
                    image2[i][j] = image[i][j];
                }
                else{
                    image2[i][j] = 255;
                }
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i][j] = image2[i][j];
            }
        }
    }
    else{ //if user enter any thing else, it is an invalid input.
        cout << "Invalid Input!" << endl;
        shrinkImage();
    }
    
    
}

//function that do blur to image.
void blurImage(){  
    cout << "hello user " << endl;
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
           if (j == (SIZE - 4)){
               image[i][j] = (image[i][j] + image[i+1][j+1] + image[i+2][j+2] + image[i+3][j+3] + image[i][j+1] + image[i][j+2] + image[i][j+3] + 
                              image[i+1][j] + image[i+1][j+2] + image[i+1][j+3] + image[i+2][j] + image[i+2][j+1] + image[i+2][j+3] + image[i+3][j] + 
                              image[i+3][j+1] + image[i+3][j+2] + image[i+4][j] + image[i+4][j+1] + image[i+4][j+2] + image[i+4][j+3]) / 25;
           }
           else if (j == (SIZE - 3)){
                image[i][j] = (image[i][j] + image[i+1][j+1] + image[i+2][j+2] + image[i][j+1] + image[i][j+2] + image[i+1][j] + image[i+1][j+2] + 
                               image[i+2][j] + image[i+2][j+1] + image[i+3][j] + image[i+3][j+1] + image[i+3][j+2] + image[i+4][j] + image[i+4][j+1] + 
                               image[i+4][j+2]) / 25;
           }
           else if (j == (SIZE - 2)){
               image[i][j] = (image[i][j] + image[i+1][j+1] + image[i][j+1] + image[i+1][j] + image[i+2][j] + image[i+2][j+1] + image[i+3][j] + 
                              image[i+3][j+1] + image[i+4][j] + image[i+4][j+1]) / 25;
           }
           else if (j == (SIZE - 1)){
               image[i][j] = (image[i][j] + image[i+1][j] + image[i+2][j] + image[i+3][j] + image[i+4][j]) / 25;
           }   
           else if (i == (SIZE - 4)){
               image[i][j] = (image[i][j] + image[i+1][j+1] + image[i+2][j+2] + image[i+3][j+3] + image[i][j+1] + image[i][j+2] + image[i][j+3] + 
                              image[i][j+4] + image[i+1][j] + image[i+1][j+2] + image[i+1][j+3] + image[i+1][j+4] + image[i+2][j] + image[i+2][j+1] + 
                              image[i+2][j+3] + image[i+2][j+4] + image[i+3][j] + image[i+3][j+1] + image[i+3][j+2] + image[i+3][j+4]) / 25;
           }
           else if (i == (SIZE - 3)){
               image[i][j] = (image[i][j] + image[i+1][j+1] + image[i+2][j+2] + image[i][j+1] + image[i][j+2] + image[i][j+3] + image[i][j+4] + 
                              image[i+1][j] + image[i+1][j+2] + image[i+1][j+3] + image[i+1][j+4] + image[i+2][j] + image[i+2][j+1] + image[i+2][j+3] + 
                              image[i+2][j+4]) / 25;
           }
           else if (i == (SIZE - 2)){
               image[i][j] = (image[i][j] + image[i+1][j+1] + image[i][j+1] + image[i][j+2] + image[i][j+3] + image[i][j+4] + image[i+1][j] + 
                              image[i+1][j+2] + image[i+1][j+3] + image[i+1][j+4]) / 25;
           }
           else if (i == (SIZE - 1)){
               image[i][j] = (image[i][j] + image[i][j+1] + image[i][j+2] + image[i][j+3] + image[i][j+4]) / 25;
           }
           else{
               image[i][j] = (image[i][j] + image[i+1][j+1] + image[i+2][j+2] + image[i+3][j+3] + image[i+4][j+4] + image[i][j+1] + image[i][j+2] + 
                              image[i][j+3] + image[i][j+4] + image[i+1][j] + image[i+1][j+2] + image[i+1][j+3] + image[i+1][j+4] + image[i+2][j] + 
                              image[i+2][j+1] + image[i+2][j+3] + image[i+2][j+4] + image[i+3][j] + image[i+3][j+1] + image[i+3][j+2] + image[i+3][j+4] + 
                              image[i+4][j] + image[i+4][j+1] + image[i+4][j+2] + image[i+4][j+3]) / 25;
           }
        }
    }
}

//the following function is ti rotate the image as the user likes
void rotateImage()
{
   
   int answer;
   cout<<"How much do you want to rotate the image?\n";
   cout<<"1- 90 degree"<<endl<<"2- 180 degree"<<endl<<"3- 270 degree"<<endl;
   cin>>answer;
   
    if(answer == 1)                //Rotate image for 90 degree.
    {
       for(int k =0 ; k<=2 ; k++)         //This loop is to repeat the code of 270 degree twice.
        {
           for (int i = 0; i < SIZE; i += 1) 
            {
                for (int j = i+1; j < SIZE; j += 1) 
                {
                    swap(image[i][j], image[j][i]);
                }
            }
            for (int i = 0; i < SIZE; i += 1) 
            {
                for (int j = 0; j < SIZE/2; j += 1) 
                {
                    swap(image[i][j], image[i][SIZE-1-j]);
                }
            }
        }
    }
    else if(answer == 2)           //Rotate image for 180 degree.
    {
        for(int k =0 ; k<=1 ; k++)       //This loop is to repeat the code of 270 degree once.
        {
            for (int i = 0; i < SIZE; i += 1) 
            {
                for (int j = i+1; j < SIZE; j += 1) 
                {
                    swap(image[i][j], image[j][i]);
                }
            }
            for (int i = 0; i < SIZE; i += 1) 
            {
                for (int j = 0; j < SIZE/2; j += 1) 
                {
                    swap(image[i][j], image[i][SIZE-1-j]);
                }
            }
        }
    }
    else if(answer == 3)           //Rotate image for 270 degree.
    {
        for (int i = 0; i < SIZE; i += 1) 
        {
            for (int j = i+1; j < SIZE; j += 1) 
            {
                swap(image[i][j], image[j][i]);
            }
        }
        for (int i = 0; i < SIZE; i += 1) 
        {
            for (int j = 0; j < SIZE/2; j += 1) 
            {
                swap(image[i][j], image[i][SIZE-1-j]);
            }
        }
    }
    else
    {
       cout<<"invalid Input!";
       rotateImage();
    }
}

void enlargeImage()     //This function is to enlarge the image 
{
    unsigned char image2[SIZE][SIZE];
    char answer;
    cout << "Which quarter do you want to enlarge? \n";
    cout << "1. First Quarter\n2. Secons Quarter\n3. Thindquarter\n4. Fourth Quarter" << endl;
    cin >> answer;
    if (answer == '1')      //This condition is for the first quarter
    {
        for (int i = 0, k = 0; i < SIZE; k++, i += 2)
        {
            for(int j = 0, z = 0; j < SIZE; z++, j += 2)
            {
                image2[i][j] = image[k][z];
                image2[i+1][j] = image[k][z];
                image2[i][j+1] = image[k][z];
                image2[i+1][j+1] = image[k][z];
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i][j] = image2[i][j];
            }
        }
    }
    else if(answer == '2')      //This condition is for the second quarter
    {
        for (int i = 0, k = 0; i < SIZE; k++, i += 2)
        {
            for(int j = 0, z = SIZE/2; j < SIZE; z++, j += 2)
            {
                image2[i][j] = image[k][z];
                image2[i+1][j] = image[k][z];
                image2[i][j+1] = image[k][z];
                image2[i+1][j+1] = image[k][z];
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i][j] = image2[i][j];
            }
        }
    }
    else if(answer == '3')      //This condition is for the third quarter
    {
        for (int i = 0, k = SIZE/2; i < SIZE; k++, i += 2)
        {
            for(int j = 0, z = 0; j < SIZE; z++, j += 2)
            {
                image2[i][j] = image[k][z];
                image2[i+1][j] = image[k][z];
                image2[i][j+1] = image[k][z];
                image2[i+1][j+1] = image[k][z];
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i][j] = image2[i][j];
            }
        }
    }
    else if(answer == '4')      //This condition is for the fourth quarter
    {
        for (int i = 0, k = SIZE/2; i < SIZE; k++, i += 2)
        {
            for(int j = 0, z = SIZE/2; j < SIZE; z++, j += 2)
            {
                image2[i][j] = image[k][z];
                image2[i+1][j] = image[k][z];
                image2[i][j+1] = image[k][z];
                image2[i+1][j+1] = image[k][z];
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i][j] = image2[i][j];
            }
        }
    }
    else
    {
        cout<<"invalid process";
        enlargeImage();
    }
}

// the following function is to detect the edges of the image
void detectEdges()
{
    // making new image to save changes in it
    unsigned char image2[SIZE][SIZE];
    int avg = 0;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image2[i][j] = 255;
            //  getting average color of image
            avg += image[i][j];
        }
    }
    avg /= (256*256);
    avg /= 3;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            // checking the surrondings pixels of  specific pixel
            if(image[i][j] - image[i+1][j] > avg || image[i][j] - image[i-1][j] > avg ||
               image[i][j] - image[i][j+1] > avg || image[i][j] - image[i][j-1] > avg || 
               image[i][j] - image[i+1][j+1] > avg || image[i][j] - image[i-1][j-1] > avg || 
               image[i][j] - image[i-1][j+1] > avg || image[i][j] - image[i+1][j-1] > avg)
            {
                image2[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            // saving the new image in the old one
            image[i][j] = image2[i][j];
        }
    }
}

// the following function is to change the grey image to balck and white
void blackAndWhite()
{
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            if(image[i][j] > 127)
            {
                image[i][j] = 255;
            }
            else
            {
                image[i][j] = 0;
            }
        }
    }
}

// the following function is to take lower half of the image and mirror it 
void mirrorLowerHalf()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = image[SIZE-i][j];
        }
    }
}

// the following function is to take right half of the image and mirror it 
void mirrorRightHalf()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = image[i][SIZE-j];
        }
    }
}

// the following function is to take upper half of the image and mirror it 
void mirrorUpperHalf()
{
    for (int i = SIZE; i > 0; i--)
    {
        for (int j = SIZE; j > 0; j--)
        {
            image[i][j] = image[SIZE-i][j];
        }
    }
}

// the following function is to take left half of the image and mirror it 
void mirrorLeftHalf()
{
    for (int i = SIZE; i > 0; i--)
    {
        for (int j = SIZE; j > 0; j--)
        {
            image[i][j] = image[i][SIZE-j];
        }
    }
}

// the following function is to flip the image on y-axis 
void flipHorizontally()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = image[i][(SIZE*2)-j];
        }
    }
}

// the following function is to flip the image on x-axis 
void flipVertically()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = image[i-SIZE][j-32];
        }
    }
}

// The following function is to invert the image
void invertImage()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = 255 - image[i][j];
        }
    }
}

void insertQuarter(unsigned char quarter[SIZE/2][SIZE/2], int row, int column)
{
    for(int i = row, x = 0; x < SIZE/2 ; x++, i++)
    {
        for(int j = column, y = 0; y < SIZE/2; y++, j++)
        {
            image[i][j] = quarter[x][y];
        }
    }
}
void makeQuarter1()
{
    for (int i = 0; i < SIZE/2; i++)
    {
        for(int j = 0; j < SIZE/2; j++)
        {
            Q1[i][j] = image[i][j];
        }
    }
}
void makeQuarter2()
{
    for(int i = 0; i < 128; i++)
    { 
        for(int j = 0, k = 127; j < 128; k++, j++)
        { 
            Q2[i][j] = image[i][k]; 
        }
    } 
}
void makeQuarter3()
{
    for(int i = 0, x = 127; i < 128; x++, i++)
    { 
        for(int j = 0; j < 128; j++)
        { 
            Q3[i][j] = image[x][j]; 
        } 
    } 
}
void makeQuarter4()
{
    for(int i = 0, x = 127; i < 128; x++, i++)
    { 
        for(int j = 0, k = 127; j < 128; k++, j++)
        { 
            Q4[i][j] = image[x][k]; 
        } 
    } 
}

void shuffleImage()
{
    makeQuarter1();
    makeQuarter2();
    makeQuarter3();
    makeQuarter4();

    string order;
    cout << "please enter the order you want to shuffle: ";
    cin >> order;

    if(order[0] == '1')
    {
        insertQuarter(Q1, 0, 0);
    }
    else if(order[0] == '2')
    {
        insertQuarter(Q2, 0, 0);
    }
    else if(order[0] == '3')
    {
        insertQuarter(Q3, 0, 0);
    }
    else if(order[0] == '4')
    {
        insertQuarter(Q4, 0, 0);
    }
    if(order[1] == '1')
    {
        insertQuarter(Q1, 0, SIZE/2);
    }
    else if(order[1] == '2')
    {
        insertQuarter(Q2, 0, SIZE/2);
    }
    else if(order[1] == '3')
    {
        insertQuarter(Q3, 0, SIZE/2);
    }
    else if(order[1] == '4')
    {
        insertQuarter(Q4, 0, SIZE/2);
    }
    if(order[2] == '1')
    {
        insertQuarter(Q1, SIZE/2, 0);
    }
    else if(order[2] == '2')
    {
        insertQuarter(Q2, SIZE/2, 0);
    }
    else if(order[2] == '3')
    {
        insertQuarter(Q3, SIZE/2, 0);
    }
    else if(order[2] == '4')
    {
        insertQuarter(Q4, SIZE/2, 0);
    }
    if(order[3] == '1')
    {
        insertQuarter(Q1, SIZE/2, SIZE/2);
    }
    else if(order[3] == '2')
    {
        insertQuarter(Q2, SIZE/2, SIZE/2);
    }
    else if(order[3] == '3')
    {
        insertQuarter(Q3, SIZE/2, SIZE/2);
    }
    else if(order[3] == '4')
    {
        insertQuarter(Q4, SIZE/2, SIZE/2);
    }
}