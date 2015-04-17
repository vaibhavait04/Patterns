// Purpose.  Template Method design pattern lab
//
// Assignment.
// o Use the Template Method pattern to refactor DirectAccessFile and
//   IndexSequentialFile into a hierarchy that demonstrates reuse of
//   implementation and interface.

/*
#include <iostream>
using namespace std;

class DirectAccessFile {
   void findDirectoryEntry() {
      cout << "find directory entry\n"; }
   void getFileTable() {
      cout << "get cylinder/track table\n"; }
   void computeTrack() {
      cout << "transform the key into its corresponding track\n"; }
   void seekToTrack() {
      cout << "seek to track\n"; }
   void findRecord() {
      cout << "read first sector\n";
      cout << "if key not found, then search track linearly to find key\n"; }
   void readRecord() {
      cout << "read record\n"; }
   void bufferOutput() {
      cout << "buffer output\n"; }
public:
   void access() {
      findDirectoryEntry();
      getFileTable();
      computeTrack();
      seekToTrack();
      findRecord();
      readRecord();
      bufferOutput();
}  };

class IndexSequentialFile {
   void findDirectoryEntry() {
      cout << "find directory entry\n"; }
   void getFileTable() {
      cout << "get cylinder/track table\n"; }
   void searchForTrack() {
      cout << "take the key and search for the track\n"; }
   void seekToTrack() {
      cout << "seek to track\n"; }
   void searchForKey() {
      cout << "search track linearly to find key\n"; }
   void readRecord() {
      cout << "read record\n"; }
   void bufferOutput() {
      cout << "buffer output\n"; }
public:
   void access() {
      findDirectoryEntry();
      getFileTable();
      searchForTrack();
      seekToTrack();
      searchForKey();
      readRecord();
      bufferOutput();
}  };

void main( void ) {
   DirectAccessFile    daf;
   daf.access();
   cout << "========================================================\n";
   IndexSequentialFile isf;
   isf.access();
}
*/
// find directory entry
// get cylinder/track table
// transform the key into its corresponding track
// seek to track
// read first sector
// if key not found, then search track linearly to find key
// read record
// buffer output
// ========================================================
// find directory entry
// get cylinder/track table
// take the key and search for the track
// seek to track
// search track linearly to find key
// read record
// buffer output




// Purpose.  Template Method design pattern answer

#include <iostream>
using namespace std;

class File {
   void findDirectoryEntry() {
      cout << "find directory entry\n"; }
   void getFileTable() {
      cout << "get cylinder/track table\n"; }
   virtual void identifyTrack() = 0;
   void seekToTrack() {
      cout << "seek to track\n"; }
   void readRecord() {
      cout << "read record\n"; }
   void bufferOutput() {
      cout << "buffer output\n"; }
protected:
   virtual void findRecord() {
      cout << "search track linearly to find key\n"; }
public:
   void access() {
      findDirectoryEntry();
      getFileTable();
      identifyTrack();
      seekToTrack();
      findRecord();
      readRecord();
      bufferOutput();
}  };

class DirectAccessFile : public File {
   /*virtual*/ void identifyTrack() {
      cout << "transform the key into its corresponding track\n"; }
   /*virtual*/ void findRecord() {
      cout << "read first sector\n";
      cout << "if key not found, then ";
      File::findRecord();
}  };

class IndexSequentialFile : public File {
   /*virtual*/ void identifyTrack() {
      cout << "take the key and search for the track\n"; }
};

void main( void ) {
   File* files[] = { &DirectAccessFile(), &IndexSequentialFile() };
   files[0]->access();
   cout << "========================================================\n";
   files[1]->access();
}

// find directory entry
// get cylinder/track table
// transform the key into its corresponding track
// seek to track
// read first sector
// if key not found, then search track linearly to find key
// read record
// buffer output
// ========================================================
// find directory entry
// get cylinder/track table
// take the key and search for the track
// seek to track
// search track linearly to find key
// read record
// buffer output

