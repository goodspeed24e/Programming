#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "leveldb/db.h"

using namespace std;


int main(int argc, char** argv)
{
    // Set up database connection information and open database
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;

    leveldb::Status status = leveldb::DB::Open(options, "./dataset/imagesDataset/imagesDB", &db);

    if (false == status.ok())
    {
        cerr << "Unable to open/create test database './dataset/imagesDataset/imagesDB'" << endl;
        cerr << status.ToString() << endl;
        return -1;
    }
	
    // Add images to the database
	ifstream::pos_type size;
	char *memblock = NULL;
	char key[64] = {0}; // the key name is SnapShot_20120817_110440.jpg

    leveldb::WriteOptions writeOptions;
    for (long i = 110440; i < 110460; ++i)
    {
		// read binary/image data
		sprintf(key, "./dataset/imagesDataset/images/SnapShot_20120817_%d.jpg", i);

		ifstream file(key, ios::in|ios::binary|ios::ate);
		if (file.is_open())
		{
			size = file.tellg();
			memblock = new char[size];
			file.seekg (0, ios::beg);
			file.read(memblock, size);
			file.close();

			// write the key into stringstream
			ostringstream keyStream;
			keyStream << key;
        
			// write the value into stringstream
			ostringstream valueStream;
			uint32_t i = 0;
			while(i<size && valueStream << memblock[i++]);
        
			db->Put(writeOptions, keyStream.str(), valueStream.str());

			delete[] memblock;
		}
    }
    
    // Iterate over each item in the database and print them
    leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
    
	fstream newImage;
    for (it->SeekToFirst(); it->Valid(); it->Next())
    {
		if (0)
		{
			int size1 = it->key().size();
			int size2 = it->value().size();
			cout << it->key().ToString() << " : " << it->value().data() << endl;
		}
		// open the new file
		ofstream newImage;
		newImage.open(it->key().ToString().insert(24,"new"), ios::out | ios::app | ios::binary);

		uint32_t i = 0;
		while(i<size && newImage << it->value().data()[i++]);
		newImage.close();
    }
    
    if (false == it->status().ok())
    {
        cerr << "An error was found during the scan" << endl;
        cerr << it->status().ToString() << endl; 
    }
    
    delete it;
    
    // Close the database
    delete db;
}

//
//int main(int argc, char** argv)
//{
//    // Set up database connection information and open database
//    leveldb::DB* db;
//    leveldb::Options options;
//    options.create_if_missing = true;
//
//    leveldb::Status status = leveldb::DB::Open(options, "./testdb", &db);
//
//    if (false == status.ok())
//    {
//        cerr << "Unable to open/create test database './testdb'" << endl;
//        cerr << status.ToString() << endl;
//        return -1;
//    }
//    
//    // Add 256 values to the database
//    leveldb::WriteOptions writeOptions;
//    for (unsigned int i = 0; i < 256; ++i)
//    {
//        ostringstream keyStream;
//        keyStream << "Key" << i;
//        
//        ostringstream valueStream;
//        valueStream << "Test data value: " << i;
//        
//        db->Put(writeOptions, keyStream.str(), valueStream.str());
//    }
//    
//    // Iterate over each item in the database and print them
//    leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
//    
//    for (it->SeekToFirst(); it->Valid(); it->Next())
//    {
//        cout << it->key().ToString() << " : " << it->value().ToString() << endl;
//    }
//    
//    if (false == it->status().ok())
//    {
//        cerr << "An error was found during the scan" << endl;
//        cerr << it->status().ToString() << endl; 
//    }
//    
//    delete it;
//    
//    // Close the database
//    delete db;
//}

