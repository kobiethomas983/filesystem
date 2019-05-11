/*                                                                                 
 Test program to show how the disk emulator API works.                             
 Author: D.M. Lyons                                                                
 Date: Spring 2017                                                                 
                                                                                   
 c 2017 dml Fordham CIS                                                            
*/                                                                                 
                                                                                   
#include<iostream>                                                                 
#include<fstream>                                                                  
#include<vector>                                                                   
                                                                                   
using namespace std;                                                               
                                                                                   
#include "disk.h" // the API/definitions for disk emulator                  
                                                                                   
int main(int argc, char **argv){                                                   
                                                                                   
  // how big do you want blocks ont he fisk, and how many of them on the disk   
                                                                                   
  int myBlockSize= 5;                                                              
  int myDiskSize = 10;                                                             
                                                                                   
                                                                                   
  // declare the disk process with these params                                    
                                                                                   
  DiskProcessType myDisk(myBlockSize,myDiskSize);                                  
                                                                                   
  // make one data buffer for a block so you can interact with the disk            
  DiskBlockType *myBuffer = new DiskBlockType(myBlockSize);                        
                                                                                   
  // turn on logging so you can see what is happening                              
  myDisk.enableLogging("disklog.txt");                                             
                                                                                   
  // fill one buffer with X                                                        
  for (int i=0; i<myBlockSize; i++) myBuffer->data[i]='X';                         
                                                                                   
  // write this to the first 5 blocks                                              
  for (int i=0; i<5; i++) myDisk.write(i,myBuffer);                                
                                                                                   
    // fill the buffer with Y                                                      
  for (int i=0; i<myBlockSize; i++) myBuffer->data[i]='Y';                         
                                                                                   
    // write this to the next 3 blocks                                             
  for (int i=5; i<8; i++) myDisk.write(i,myBuffer);                                
                                                                                   
                                                                                   
  // what if you just want to change  byte 3 in block 2?                           
                                                                                   
  myDisk.read(2,myBuffer);                                                         
  myBuffer->data[3]='Z';                                                           
  myDisk.write(2,myBuffer);                                                        
                                                                                   
  //log some stats about what has gone on up to now       
    myDisk.writeStats();                                                         
                                                                                
                                                                                
   // read all the stuff from the disk                                          
                                                                                
   for (int i=0; i<10; i++) {                                                   
     myDisk.read(i,myBuffer);                                                   
     // print comtents to the screen                                            
     cout<<"Block "<<i<<" : ";                                                  
     for (int j=0; j<myBlockSize; j++) cout << myBuffer->data[j];               
     cout<<"\n";                                                                
   }                                                                            
                                                                                
   cout<<"try to read/write some bad block numbers\n";                          
   myDisk.read(-1,myBuffer);                                                    
   myDisk.write(-1,myBuffer);                                                   
                                                                                
   myDisk.read(myDiskSize+1,myBuffer);                                          
   myDisk.write(myDiskSize+1,myBuffer);                                         
                                                                                
   cout<<"try to read/write some bad block sizes\n";                            
   DiskBlockType *myBuffer1 = new DiskBlockType(myBlockSize-1);                 
   myDisk.read(0,myBuffer1);                                                    
   myDisk.write(0,myBuffer1);                                                   
                                                                                
   delete myBuffer;                                                             
   delete myBuffer1;                                                            
   // terminating will clean up the disk via chaining destructors               
}                                                                                 