// ITP 365 Fall 2018
// HW6 - Doubly Linked List and Movie Player
// Name: Mara Pleasure
// Email: mpleasur@usc.edu
// Platform: Mac
//

#include "MoviePlayer.h"

// Function: Parameterized Constructor
// Purpose: Sets member variables to input, clears list, and calls loader
// Input: None
// Returns: Nothing
MoviePlayer::MoviePlayer(std::string filmName)
{
    //clear the film
    mFilm.clear();
    //set frame to 0
    currFrameNum = 0;
    //set film to entered name
    mFilmName = filmName;
    //set iterator to start
    pos = mFilm.begin();
    
    //load tape
    loadTape();
    
}

// Function: Destructor
// Purpose: Empties the list
// Input: None
// Returns: Nothing
MoviePlayer::~MoviePlayer()
{
    //clears the film
    mFilm.clear();
}

// Function: goFwrd
// Purpose: Moves the current "frame" forward by 1 frame
// Also keeps track of how many frames have been viewed
// Shouldn't go past the end of the movie
// Input: None
// Returns: Nothing
void MoviePlayer::goFwrd()
{
    //this function should move the tape forward by 1 frame. It should also increment currFrameNum counter;
    if (pos != mFilm.end()){
        pos++;
        currFrameNum = currFrameNum + 1;
    }
    
}

// Function: goBack
// Purpose: Moves the current "frame" backward by 1 frame
// Also keeps track of how many frames have been viewed
// Shouldn't go past the end of the movie
// Input: None
// Returns: Nothing
void MoviePlayer::goBack()
{
    //decrements
    pos--;
    currFrameNum = currFrameNum - 1;
}

// Function: rewind
// Purpose: Moves the current "frame" to the movie's beginning again
// Input: None
// Returns: Nothing
void MoviePlayer::rewind()
{
    //rewinds film to beginning
    pos = mFilm.begin();
    //sets curFrame num to 0
    currFrameNum = 0;
}

// Function: getCurrFrame
// Purpose: Gets the string that contains the current "frame" as stored
// in the list "mFilm"
// Input: None
// Returns: String with the current "frame"
std::string MoviePlayer::getCurrFrame()
{

    //dereferences pos
    return *pos;
}

// Function: delCurrFrame
// Purpose: Deletes the current frame, moves forward to the next one
// Also keeps track of how many frames have been viewed
// Input: None
// Returns: Nothing
void MoviePlayer::delCurrFrame()
{
    //if its not a null ptr, erase
    if (pos->mNext != nullptr){
          pos = mFilm.erase(pos);
    }
    
    
}

// Function: copyCurrFrame
// Purpose: Copies current frame and places the copy BEFORE the current frame
// Also keeps track of how many frames have been viewed
// Input: None
// Returns: Nothing
void MoviePlayer::copyCurrFrame()//CONFUSED
{
    // create another stringg
    std::string copy;
    copy = getCurrFrame();
    //set equal to getcurrentframe();
    mFilm.insert(pos, copy);
    //insert copy at mFilm.insert(pos,copy)
}

// Function: getCurrFrameNum
// Purpose: Gets the "index" that corresponds to the current frame
// Input: None
// Returns: Number of frames that have been viewed
unsigned MoviePlayer::getCurrFrameNum() const
{
    //returns the current frame
    return currFrameNum;
}

// Function: getNumFrames
// Purpose: Gets the total number of frames in the movie
// Input: None
// Returns: The overall number of frames in the movie
unsigned int MoviePlayer::getNumFrames() const
{
   //returns size of itp double list
    return mFilm.size(); // FIX RETURN VALUE
}

// Function: getFrameSize
// Purpose: Gives the number of lines in a frame
// For how big the "screen" for the film should be
// Input: None
// Returns: The value stored in FRAMESIZE
unsigned int MoviePlayer::getFrameSize() const
{
    //returns framesize
    return FRAMESIZE; // FIX RETURN VALUE
}

// Function: getCurrFrame
// Purpose: Retrieves the current "frame" from the film list
// Modifies the inputted vector of GLabels to contain the current frame
// Input: A vector of "GLabels" that are the "screen" -- passed by reference
// Returns: Nothing
void MoviePlayer::getCurrFrame(Vector<GLabel*>& screen)
{
    //makes a string with cur frame name
    std::string curFrame = getCurrFrame();
    //makes a string stream
    std::stringstream frame(curFrame);
    for(int i = 0; i<screen.size(); i++){
        //gets line and adds to frame
        getline(frame, curFrame);
        //set label cur frame
        screen[i]->setLabel(curFrame);
    }
}

// Function: loadTape
// Purpose: Uses mFilmName (set by constructor) to fill
// mFilm with strings that make up the movie to display
// Input: None
// Returns: Nothing
void MoviePlayer::loadTape() //CONFUSED
{
    //set up strings to hold stuff
    std::string num;
    std::string frame;
    std::string line;
    //number to hold number of times you do frame
    int number;
    //1. open file
    std::ifstream fileInput(mFilmName);
    //  if it doesnt open throw an error
    if (!fileInput.is_open()){
        error("File did not open");
    }
    //while not at end of file
    while(!fileInput.eof()){
        //get the line with the num
        getline(fileInput,num);
        //if num is not empty
        if (!num.empty()){
            number = std::stoi(num);
            //gets all the lines for the length of the frame
            for (int i=0; i<FRAMESIZE; i++){
                getline(fileInput, line);
                //adds it to a string
                frame += line + " \n";
            }
            for (int j=0; j<number; j++){
                //pushes back onto mFilm for number of times supposed to show frame
                mFilm.push_back(frame);
            }
        }
        else if (num.empty()){
            getline(fileInput, num);
        }
        
    }
    
    
    //how files look
    //number
    //13 lines of frame
    //number
    //13 lines of frame
}
