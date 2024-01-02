#include<iostream>
#include<fstream>
#include<cstring>
#include<cmath>
#include<stdlib.h>
#include"bmplib.cpp"

using namespace std;

// Images which will be used in the program.
// Using 3D arrays for RGB images.
unsigned char image[SIZE][SIZE][RGB];  // To load main image.
unsigned char image2[SIZE][SIZE][RGB]; // To load second image if needed.
unsigned char Q1[SIZE/2][SIZE/2][RGB]; // Q1 for suffle.
unsigned char Q2[SIZE/2][SIZE/2][RGB]; // Q2.
unsigned char Q3[SIZE/2][SIZE/2][RGB]; // Q3.
unsigned char Q4[SIZE/2][SIZE/2][RGB]; // Q4.

// Prototypes.
void loadImage();
void saveImage();
void loadSecondImage();
void mirrorLowerHalf();
void mirrorUpperHalf();
void mirrorRightHalf();
void mirrorLeftHalf();
void flipHorizontally();
void flipVertically();
void rotateImageBy90();
void rotateImageBy180();
void rotateImageBy270();
void blackAndWhite();
void edgeDetection();
void mergeImages();
void darkenImage();
void lightenImage();
void invertImage();
void enlargeImage();
void blurImage();
void shrinkImage();
void insertQuarter(unsigned char quarter[SIZE/2][SIZE/2][RGB],int row,int column);
void makeQuarter1();
void makeQuarter2();
void makeQuarter3();
void makeQuarter4();
void shuffleImage();

// Get users choice to see which filter he wants to try.
// Calling functions needed for user's filters to be done.
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
        int ans2;
        cout << "1. Darken\n2. Lighten" << endl;
        cin >> ans2;
        if(ans2 == 1)
        {
            loadImage();
            darkenImage();
            saveImage();
            main();
        }
        else if(ans2 == 2)
        {
            loadImage();
            lightenImage();
            saveImage();
            main();
        }
        else
        {
            cout << "Invalid input" << endl;
            main();
        }
    }
    else if(ans == '6')
    {
        int ans2;
        cout << "by which degree do you want to rotate" << endl;
        cout << "1. 90\n2. 180\n3. 270" << endl;
        cin >> ans2;
        if(ans2 == 1)
        {
            loadImage();
            rotateImageBy90();
            saveImage();
            main();
        }
        else if(ans2 == 2)
        {
            loadImage();
            rotateImageBy180();
            saveImage();
            main();
        }
        else if(ans == 3)
        {
            loadImage();
            rotateImageBy270();
            saveImage();
            main();
        }
        else
        {
            cout << "Invalid input" << endl;
            main();
        }
    }
    else if(ans == '7')
    {
        loadImage();
        edgeDetection();
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

// Load image which the user wants to filter.
void loadImage()
{
    char imageName[50];
    cout << "Enter image Name: ";
    cin >> imageName;

    strcat(imageName, ".bmp");
    readRGBBMP(imageName, image);
}

// Load second image from user if needed.
void loadSecondImage()
{
    char imageName[50];
    cout << "Enter second image name: ";
    cin >> imageName;

    strcat (imageName, ".bmp");
    readRGBBMP(imageName, image2);
}

// Save the edited image with the user's name choice.
void saveImage()
{
    char saveImage[50];
    cout << "Enter taget file Name: ";
    cin >> saveImage;

    strcat(saveImage, ".bmp");
    writeRGBBMP(saveImage, image);
}

// Function to change the grey image to balck and white.
void blackAndWhite()
{
    int avg = 0;
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            avg = image[i][j][0] + image[i][j][1] + image[i][j][2]; // Getting average color of each pixel to compare with it.
            avg /= 3;
            if(avg > 127)
            {
                image[i][j][0] = 255;
                image[i][j][1] = 255;
                image[i][j][2] = 255;
            }
            else
            {
                image[i][j][0] = 0;
                image[i][j][1] = 0;
                image[i][j][2] = 0;
            }
        }
    }
   
}

// Function is to take lower half of the image and mirror it. 
void mirrorLowerHalf()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for(int k = 0; k < SIZE; k++)
            {
                image[i][j][k] = image[SIZE-i][j][k];
            }
        }
    }
}

// Function is to take right half of the image and mirror it.
void mirrorRightHalf()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for(int k = 0; k < RGB; k++)
            {
                image[i][j][k] = image[i][SIZE-j][k];
            }
        }
    }
}

// Function is to take upper half of the image and mirror it.
void mirrorUpperHalf()
{
    for (int i = SIZE; i > 0; i--)
    {
        for (int j = SIZE; j > 0; j--)
        {
            for(int k = SIZE; k > 0; k--)
            {
                image[i][j][k] = image[SIZE-i][j][k];
            }
        }
    }
}

// Function is to take left half of the image and mirror it.
void mirrorLeftHalf()
{
    for (int i = SIZE; i > 0; i--)
    {
        for (int j = SIZE; j > 0; j--)
        {
            for(int k = RGB; k > 0; k--)
            {
                image[i][j][k] = image[i][SIZE-j][k];
            }
        }
    }
}

// Function is to flip the image on y-axis.
void flipHorizontally()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for(int k = 0; k < RGB; k++)
            {
                image[i][j][k] = image[i][(SIZE*2)-j][k];
            }
        }
    }
}

// Function is to flip the image on x-axis.
void flipVertically()
{
    rotateImageBy180();
    flipHorizontally();
}

// The following function is to rotate the image by 90 degrees.
void rotateImageBy90()
{
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = i+1; j < SIZE; j++) 
        {
            for(int k = 0; k < RGB; k++)
            {
                swap(image[i][j][k], image[j][i][k]);
            }
        }
    }
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE/2; j++) 
        {
            for(int k = 0; k < RGB; k++)
            {
                swap(image[i][j][k], image[i][SIZE-1-j][k]);
            }
        }
    }
}

// The following function is to rotate the image by 180 degrees.
void rotateImageBy180()
{
    for(int l = 0 ; l <= 1 ; l++)       
    {
        for (int i = 0; i < SIZE; i++) 
        {
            for (int j = i+1; j < SIZE; j++) 
            {
                for(int k = 0; k < RGB; k++)
                {
                    swap(image[i][j][k], image[j][i][k]);
                }
            }
        }
        for (int i = 0; i < SIZE; i++) 
        {
            for (int j = 0; j < SIZE/2; j++) 
            {
                for(int k = 0; k < RGB; k++)
                {
                    swap(image[i][j][k], image[i][SIZE-1-j][k]);
                }
            }
        }
    }
}

// The following function is to rotate the image by 270 degrees.
void rotateImageBy270()
{
    for(int l = 0 ; l <= 2 ; l++)       
    {
        for (int i = 0; i < SIZE; i++) 
        {
            for (int j = i+1; j < SIZE; j++) 
            {
                for(int k = 0; k < RGB; k++)
                {
                    swap(image[i][j][k], image[j][i][k]);
                }
            }
        }
        for (int i = 0; i < SIZE; i++) 
        {
            for (int j = 0; j < SIZE/2; j++) 
            {
                for(int k = 0; k < RGB; k++)
                {
                    swap(image[i][j][k], image[i][SIZE-1-j][k]);
                }
            }
        }
    }
}

// The following function is to detect the edges of the image.
void edgeDetection()
{
    int avg = 0, avg2 = 0;
    // Making new image to save changes in it.
    unsigned char image2[SIZE][SIZE][RGB];
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            avg = image[i][j][0] + image[i][j][1] + image[i][j][2];
            avg /= 3;
            image[i][j][0] = avg; // Getting average color of a each pixel.
            image[i][j][1] = avg; // Each pixel equals its average color.
            image[i][j][2] = avg;
        }
    }
    for (int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            image2[i][j][0] = 255;
            image2[i][j][1] = 255; // Getting average color of image after change.
            image2[i][j][2] = 255;
            avg2 += image[i][j][0] + image[i][j][1] + image[i][j][2];
        }
    }
    avg2 /= (256*256);
    avg2 /= 3;
    avg2 /= 3;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            // Checking the surrondings pixels of specific pixel.
            if((image[i][j][0] + image[i][j][1] + image[i][j][2]) - (image[i+1][j][0] + image[i+1][j][1] + image[i+1][j][2]) > avg2
            || (image[i][j][0] + image[i][j][1] + image[i][j][2]) - (image[i-1][j][0] + image[i-1][j][1] + image[i-1][j][2]) > avg2 
            || (image[i][j][0] + image[i][j][1] + image[i][j][2]) - (image[i][j+1][0] + image[i][j+1][1] + image[i][j+1][2]) > avg2 
            || (image[i][j][0] + image[i][j][1] + image[i][j][2]) - (image[i][j-1][0] + image[i][j-1][1] + image[i][j-1][2]) > avg2 
            || (image[i][j][0] + image[i][j][1] + image[i][j][2]) - (image[i+1][j+1][0] + image[i+1][j+1][1] + image[i+1][j+1][2]) > avg2 
            || (image[i][j][0] + image[i][j][1] + image[i][j][2]) - (image[i-1][j-1][0] + image[i-1][j-1][1] + image[i-1][j-1][2]) > avg2
            || (image[i][j][0] + image[i][j][1] + image[i][j][2]) - (image[i-1][j+1][0] + image[i-1][j+1][1] + image[i-1][j+1][2]) > avg2 
            || (image[i][j][0] + image[i][j][1] + image[i][j][2]) - (image[i+1][j-1][0] + image[i+1][j-1][1] + image[i+1][j-1][2]) > avg2)
            {
                image2[i][j][0] = 0;
                image2[i][j][1] = 0;
                image2[i][j][2] = 0;
            }
        }
    }
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j][0] = image2[i][j][0];
            image[i][j][1] = image2[i][j][1];  // Saving the new image in the old one.
            image[i][j][2] = image2[i][j][2];
        }
    }
}

// Function that merge two images together.
void mergeImages()
{
    loadSecondImage();
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) // This nested for loop add the average color of the two images together.
        {
            image[i][j][0] = ((image[i][j][0] + image2[i][j][0])/2);
            image[i][j][1] = ((image[i][j][1] + image2[i][j][1])/2);
            image[i][j][2] = ((image[i][j][2] + image2[i][j][2])/2);
        }
    }
}

// Function that darken the image.
void darkenImage()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j][0] = image[i][j][0]/2;
            image[i][j][1] = image[i][j][1]/2;
            image[i][j][2] = image[i][j][2]/2;
        }
    }
}

// Function that lighten the image.
void lightenImage()
{
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            for(int k = 0; k < RGB; k++)
            {
                if(image[i][j][k] <= 170 && image[i][j][k] > 0)  
                {
                    image[i][j][k] += 85;
                } 
                else if(image[i][j][k] > 170)
                {
                    image[i][j][k] = 255;
                }
                else if(image[i][j][k] == 0)
                {
                    image[i][j][k] = 85;
                }
            }
        }
    }
}

// Function is to invert the image.
void invertImage()
{
    int avg = 0;
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            avg = image[i][j][0] + image[i][j][1] + image[i][j][2];
            avg /= 3;
            image[i][j][0] = avg;
            image[i][j][1] = avg; // Changing each pixel color to its average color.
            image[i][j][2] = avg;
        }
    }

    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            for(int k = 0; k < RGB; k++)
            {
                image[i][j][0] = 255 - image[i][j][0];
                image[i][j][1] = 255 - image[i][j][1];
                image[i][j][2] = 255 - image[i][j][2];
            }
        }
    }
}

// This function is to enlarge the image. 
void enlargeImage()
{
    unsigned char image2[SIZE][SIZE][RGB];
    char answer;
    cout << "Which quarter do you want to enlarge? \n";
    cout << "1. First Quarter\n2. Secons Quarter\n3. Thindquarter\n4. Fourth Quarter" << endl;
    cin >> answer;
    if (answer == '1') // This condition is for the first quarter.
    {
        for (int i = 0, x = 0; i < SIZE; x++, i += 2)
        {
            for(int j = 0, y = 0; j < SIZE; y++, j += 2)
            {
                for(int k = 0; k < RGB; k++)
                {
                    image2[i][j][k] = image[x][y][k];
                    image2[i+1][j][k] = image[x][y][k];
                    image2[i][j+1][k] = image[x][y][k];
                    image2[i+1][j+1][k] = image[x][y][k];
                }
            }
        }
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                for(int k = 0; k < RGB; k++)
                {
                    image[i][j][k] = image2[i][j][k];
                }
            }
        }
    }
    else if(answer == '2') // This condition is for the second quarter.
    {
        for (int i = 0, x = 0; i < SIZE; x++, i += 2)
        {
            for(int j = 0, y = SIZE/2; j < SIZE; y++, j += 2)
            {
                for(int k = 0; k < RGB; k++)
                {
                    image2[i][j][k] = image[x][y][k];
                    image2[i+1][j][k] = image[x][y][k];
                    image2[i][j+1][k] = image[x][y][k];
                    image2[i+1][j+1][k] = image[x][y][k];
                }
            }
        }

        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                for(int k = 0; k < RGB; k++)
                {
                    image[i][j][k] = image2[i][j][k];
                }
            }
        }
    }
    else if(answer == '3') // This condition is for the third quarter.
    {
        for (int i = 0, x = SIZE/2; i < SIZE; x++, i += 2)
        {
            for(int j = 0, y = 0; j < SIZE; y++, j += 2)
            {
                for(int k = 0; k < RGB; k++) 
                {
                    image2[i][j][k] = image[x][y][k];
                    image2[i+1][j][k] = image[x][y][k];
                    image2[i][j+1][k] = image[x][y][k];
                    image2[i+1][j+1][k] = image[x][y][k];
                }
            }
        }
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                for(int k = 0; k < RGB; k++)
                {
                    image[i][j][k] = image2[i][j][k];
                }
            }
        }
    }
    else if(answer == '4') // This condition is for the fourth quarter.
    {
        for (int i = 0, x = SIZE/2; i < SIZE; x++, i += 2)
        {
            for(int j = 0, y = SIZE/2; j < SIZE; y++, j += 2)
            {
                for(int k = 0; k < RGB; k++)
                {
                    image2[i][j][k] = image[x][y][k];
                    image2[i+1][j][k] = image[x][y][k];
                    image2[i][j+1][k] = image[x][y][k];
                    image2[i+1][j+1][k] = image[x][y][k];
                }
            }
        }
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                for(int k = 0; k < RGB; k++)
                {
                    image[i][j][k] = image2[i][j][k];
                }
            }
        }
    }
    else
    {
        cout << "invalid process";
    }
}

// Function that Blur the image.
void blurImage()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for(int k = 0; k < RGB; k++)
            {
                if (j == (SIZE - 4))
                {
                    image[i][j][k] = (image[i][j][k] + image[i+1][j+1][k] + image[i+2][j+2][k] + image[i+3][j+3][k] + image[i][j+1][k] + image[i][j+2][k] + 
                                    image[i][j+3][k] + image[i+1][j][k] + image[i+1][j+2][k] + image[i+1][j+3][k] + image[i+2][j][k] + image[i+2][j+1][k] + 
                                    image[i+2][j+3][k] + image[i+3][j][k] + image[i+3][j+1][k] + image[i+3][j+2][k] + image[i+4][j][k] + image[i+4][j+1][k] + 
                                    image[i+4][j+2][k] + image[i+4][j+3][k]) / 25;
                }
                else if (j == (SIZE - 3))
                {
                        image[i][j][k] = (image[i][j][k] + image[i+1][j+1][k] + image[i+2][j+2][k] + image[i][j+1][k] + image[i][j+2][k] + image[i+1][j][k] + 
                                       image[i+1][j+2][k] + image[i+2][j][k] + image[i+2][j+1][k] + image[i+3][j][k] + image[i+3][j+1][k] + image[i+3][j+2][k] + 
                                       image[i+4][j][k] + image[i+4][j+1][k] + image[i+4][j+2][k]) / 25;
                }
                else if (j == (SIZE - 2))
                {
                    image[i][j][k] = (image[i][j][k] + image[i+1][j+1][k] + image[i][j+1][k] + image[i+1][j][k] + image[i+2][j][k] + image[i+2][j+1][k] + 
                                   image[i+3][j][k] + image[i+3][j+1][k] + image[i+4][j][k] + image[i+4][j+1][k]) / 25;
                }
                else if (j == (SIZE - 1))
                {
                    image[i][j][k] = (image[i][j][k] + image[i+1][j][k] + image[i+2][j][k] + image[i+3][j][k] + image[i+4][j][k]) / 25;
                }   
                else if (i == (SIZE - 4))
                {
                    image[i][j][k] = (image[i][j][k] + image[i+1][j+1][k] + image[i+2][j+2][k] + image[i+3][j+3][k] + image[i][j+1][k] + image[i][j+2][k] + 
                                      image[i][j+3][k] + image[i][j+4][k] + image[i+1][j][k] + image[i+1][j+2][k] + image[i+1][j+3][k] + image[i+1][j+4][k] + 
                                      image[i+2][j][k] + image[i+2][j+1][k] + image[i+2][j+3][k] + image[i+2][j+4][k] + image[i+3][j][k] + image[i+3][j+1][k] + 
                                      image[i+3][j+2][k] + image[i+3][j+4][k]) / 25;
                }
                else if (i == (SIZE - 3))
                {
                    image[i][j][k] = (image[i][j][k] + image[i+1][j+1][k] + image[i+2][j+2][k] + image[i][j+1][k] + image[i][j+2][k] + image[i][j+3][k] + 
                                  image[i][j+4][k] + image[i+1][j][k] + image[i+1][j+2][k] + image[i+1][j+3][k] + image[i+1][j+4][k] + image[i+2][j][k] + 
                                  image[i+2][j+1][k] + image[i+2][j+3][k] + image[i+2][j+4][k]) / 25;
                }
                else if (i == (SIZE - 2))
                {
                    image[i][j][k] = (image[i][j][k] + image[i+1][j+1][k] + image[i][j+1][k] + image[i][j+2][k] + image[i][j+3][k] + image[i][j+4][k] + 
                                      image[i+1][j][k] + image[i+1][j+2][k] + image[i+1][j+3][k] + image[i+1][j+4][k]) / 25;
                }
                else if (i == (SIZE - 1))
                {
                    image[i][j][k] = (image[i][j][k] + image[i][j+1][k] + image[i][j+2][k] + image[i][j+3][k] + image[i][j+4][k]) / 25;
                }
                else
                {
                    image[i][j][k] = (image[i][j][k] + image[i+1][j+1][k] + image[i+2][j+2][k] + image[i+3][j+3][k] + image[i+4][j+4][k] + image[i][j+1][k]+ 
                                      image[i][j+2][k] + image[i][j+3][k] + image[i][j+4][k] + image[i+1][j][k] + image[i+1][j+2][k] + image[i+1][j+3][k] + 
                                      image[i+1][j+4][k] + image[i+2][j][k] + image[i+2][j+1][k] + image[i+2][j+3][k] + image[i+2][j+4][k] + image[i+3][j][k] + 
                                      image[i+3][j+1][k] + image[i+3][j+2][k] + image[i+3][j+4][k] + image[i+4][j][k] + image[i+4][j+1][k] + image[i+4][j+2][k] + 
                                      image[i+4][j+3][k]) / 25;
                }
            }
        }
    }
}

// Function that shrink image to: 1/2 or 1/3 or 1/4.
void shrinkImage()
{
    unsigned char image2[SIZE][SIZE][RGB];
    int ans;
    cout << "Shrink image to::\n1. Half.\n2. Third. \n3. Quarter.\n"; // Ask user.
    cin >> ans;
    if (ans == 1)
    { // Shrink to 1/2.
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for(int k = 0; k < RGB; k++)
                {
                    image[i/2][j/2][k] = (image[i][j][k] + image[i+1][j][k] + image[i][j+1][k] + image[i+1][j+1][k]) / 4;
                }
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for(int k = 0; k < RGB; k++)
                {
                    if (i < 127 && j < 127)
                    {
                        image2[i][j][k] = image[i][j][k];
                    }
                    else{
                        image2[i][j][k] = 255;
                    }
                }
            }
        }
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                for(int k = 0; k < RGB; k++)
                {
                    image[i][j][k] = image2[i][j][k];
                }
            }
        }
    }
    else if (ans == 2)
    { // Shrink to 1/3.
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for(int k = 0; k < RGB; k++)
                {
                    image[i/3][j/3][k] = (image[i][j][k] + image[i+1][j][k] + image[i+2][j][k] + image[i][j+1][k] + image[i][j+2][k] + image[i+2][j+2][k] + 
                                       image[i+1][j+2][k] + image[i+2][j+1][k] + image[i+1][j+1][k]) / 9;
                }
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for(int k = 0; k < RGB; k++)
                {
                    if (i < 85 && j < 85)
                    {
                        image2[i][j][k] = image[i][j][k];
                    }
                    else
                    {
                        image2[i][j][k] = 255;
                    }
                }
            }
        }
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                for(int k = 0; k < RGB; k++)
                {
                    image[i][j][k] = image2[i][j][k];
                }
            }
        }
    }
    else if (ans == 3)
    { // Shrink to 1/4.
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for(int k = 0; k < RGB; k++)
                {
                    image[i/4][j/4][k] = (image[i][j][k] + image[i+1][j][k] + image[i+2][j][k] + image[i][j+1][k] + image[i][j+2][k] + image[i+2][j+2][k] + 
                                       image[i+1][j+2][k] + image[i+2][j+1][k] + image[i+1][j+1][k] + image[i+3][j][k] + image[i][j+3][k] + image[i+3][j+3][k] + 
                                       image[i+1][j+3][k] + image[i+2][j+3][k] + image[i+3][j+1][k]+ image[i+3][j+2][k]) / 16;
                }
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for(int k = 0; k < RGB; k++)
                {
                    if (i < 64 && j < 64)
                    {
                        image2[i][j][k] = image[i][j][k];
                    }
                    else{
                        image2[i][j][k] = 255;
                    }
                }
            }
        }
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                for(int k = 0; k < RGB; k++)
                {
                    image[i][j][k] = image2[i][j][k];
                }
            }
        }
    }
    else{
        cout << "Invalid input" << endl;
    }
}

// Take the quarter and see where it starts and ends and save it in the image.
void insertQuarter(unsigned char quarter[SIZE/2][SIZE/2][RGB], int row, int column, int k)
{
    for(int i = row, x = 0; x < SIZE/2 ; x++, i++)
    {
        for(int j = column, y = 0; y < SIZE/2; y++, j++)
        {
            for(int k = 0; k < RGB; k++)
            {
                image[i][j][k] = quarter[x][y][k];
            }
        }
    }
}
// Function to save Quarter One.
void makeQuarter1()
{
    for (int i = 0; i < SIZE/2; i++)
    {
        for(int j = 0; j < SIZE/2; j++)
        {
            for(int k = 0; k < RGB; k++)
            {
                Q1[i][j][k] = image[i][j][k];
            }
        }
    }
}
// Function to save Quarter Two.
void makeQuarter2()
{
    for(int i = 0; i < 128; i++)
    { 
        for(int j = 0, x = 127; j < 128; x++, j++)
        { 
            for(int k = 0; k < RGB; k++)
            {
                Q2[i][j][k] = image[i][x][k];
            } 
        }
    } 
}
// Function to save Quarter Three.
void makeQuarter3()
{
    for(int i = 0, x = 127; i < 128; x++, i++)
    { 
        for(int j = 0; j < 128; j++)
        { 
            for(int k = 0; k < RGB; k++)
            {
                Q3[i][j][k] = image[x][j][k]; 
            }
        } 
    } 
}
// Function to save Quarter Four.
void makeQuarter4()
{
    for(int i = 0, x = 127; i < 128; x++, i++)
    { 
        for(int j = 0, y = 127; j < 128; y++, j++)
        { 
            for(int k = 0; k < RGB; k++)
            {
                Q4[i][j][k] = image[x][y][k]; 
            }
        } 
    } 
}

// function to shuffle the image with user's input.
void shuffleImage()
{
    makeQuarter1();
    makeQuarter2(); // Divide the four quarters of the image.
    makeQuarter3();
    makeQuarter4();

    string order;
    cout << "please enter the order you want to shuffle: ";
    cin >> order;

    // Check the order and output the final image according to this order.
    if(order[0] == '1')
    {
        insertQuarter(Q1, 0, 0, 0);
        insertQuarter(Q1, 0, 0, 1);
        insertQuarter(Q1, 0, 0, 2);
    }
    else if(order[0] == '2')
    {
        insertQuarter(Q2, 0, 0, 0);
        insertQuarter(Q2, 0, 0, 1);
        insertQuarter(Q2, 0, 0, 2);
    }
    else if(order[0] == '3')
    {
        insertQuarter(Q3, 0, 0, 0);
        insertQuarter(Q3, 0, 0, 1);
        insertQuarter(Q3, 0, 0, 2);
    }
    else if(order[0] == '4')
    {
        insertQuarter(Q4, 0, 0, 0);
        insertQuarter(Q4, 0, 0, 1);
        insertQuarter(Q4, 0, 0, 2);
    }
    if(order[1] == '1')
    {
        insertQuarter(Q1, 0, SIZE/2, 0);
        insertQuarter(Q1, 0, SIZE/2, 1);
        insertQuarter(Q1, 0, SIZE/2, 2);
    }
    else if(order[1] == '2')
    {
        insertQuarter(Q2, 0, SIZE/2, 0);
        insertQuarter(Q2, 0, SIZE/2, 1);
        insertQuarter(Q2, 0, SIZE/2, 2);
    }
    else if(order[1] == '3')
    {
        insertQuarter(Q3, 0, SIZE/2, 0);
        insertQuarter(Q3, 0, SIZE/2, 1);
        insertQuarter(Q3, 0, SIZE/2, 2);
    }
    else if(order[1] == '4')
    {
        insertQuarter(Q4, 0, SIZE/2, 0);
        insertQuarter(Q4, 0, SIZE/2, 1);
        insertQuarter(Q4, 0, SIZE/2, 2);
    }
    if(order[2] == '1')
    {
        insertQuarter(Q1, SIZE/2, 0, 0);
        insertQuarter(Q1, SIZE/2, 0, 1);
        insertQuarter(Q1, SIZE/2, 0, 2);
    }
    else if(order[2] == '2')
    {
        insertQuarter(Q2, SIZE/2, 0, 0);
        insertQuarter(Q2, SIZE/2, 0, 1);
        insertQuarter(Q2, SIZE/2, 0, 2);
    }
    else if(order[2] == '3')
    {
        insertQuarter(Q3, SIZE/2, 0 ,0);
        insertQuarter(Q3, SIZE/2, 0 ,1);
        insertQuarter(Q3, SIZE/2, 0 ,2);
    }
    else if(order[2] == '4')
    {
        insertQuarter(Q4, SIZE/2, 0, 0);
        insertQuarter(Q4, SIZE/2, 0, 1);
        insertQuarter(Q4, SIZE/2, 0, 2);
    }
    if(order[3] == '1')
    {
        insertQuarter(Q1, SIZE/2, SIZE/2, 0);
        insertQuarter(Q1, SIZE/2, SIZE/2, 1);
        insertQuarter(Q1, SIZE/2, SIZE/2, 2);
    }
    else if(order[3] == '2')
    {
        insertQuarter(Q2, SIZE/2, SIZE/2, 0);
        insertQuarter(Q2, SIZE/2, SIZE/2, 1);
        insertQuarter(Q2, SIZE/2, SIZE/2, 2);
    }
    else if(order[3] == '3')
    {
        insertQuarter(Q3, SIZE/2, SIZE/2, 0);
        insertQuarter(Q3, SIZE/2, SIZE/2, 1);
        insertQuarter(Q3, SIZE/2, SIZE/2, 2);
    }
    else if(order[3] == '4')
    {
        insertQuarter(Q4, SIZE/2, SIZE/2, 0);
        insertQuarter(Q4, SIZE/2, SIZE/2, 1);
        insertQuarter(Q4, SIZE/2, SIZE/2, 2);
    }
}