/*
 * test_func.cpp
 *
 *  Created on: Nov 6, 2018
 *      Author: murthk5
 */




/*
 * test_function.cpp
 *
 *  Created on: Nov 5, 2018
 *      Author: murthk5
 */
#include<iostream>
#include <chrono>
#include<string>
#include<fstream>
#include "../keshav_hashmap/hashmap.h"
#include "../keshav_hashmap/hashmap.cpp"

#define abc 10

using namespace std::chrono;

enum {INTvsINT=1,INTvsSTRING=2,INTvsFLOAT=3,INTvsOBJECT=4,DESTRUCT_EXPLICIT=5,ITERATORINTVSINT=6,COLLISION_INTVSFLOAT_AT_SLOT=7};


struct Student
{
	int age;
	string name;
	int marks;
};

Student stu;

class Time_Set
{
public:	 steady_clock::time_point initial;
		 steady_clock::time_point final;
		 steady_clock::duration time_span;
		 double nseconds;
		 Time_Set()
		 {
			 initial=steady_clock::now();
		 }

	 double clock_end()
	{
		final = steady_clock::now();

		time_span = initial - final;

		nseconds = double(time_span.count()) * steady_clock::period::num / steady_clock::period::den;

		return nseconds;
	}

};
int main()
{
int choice;
	int keyInputIntvsInt,valInputIntvsInt;

	int keyInputIntvsString;
	string valInputIntvsString;


	float valInputIntvsFloat;
	int keyInputIntvsFloat;

	int keyInputIntvsObject;

	int keyDel;
	int keyValFind;

	uint32_t slotNumber;
	uint32_t slotCollis;

	MyHashmap<int, int> objIntvsInt;
	MyHashmap<int, string> objIntvsString;
	MyHashmap<int, float> objIntvsFloat;
	MyHashmap<int, Student> objIntvsObject;


	ifstream iFile_INTVSINT;
	ifstream iFile_INTVSSTRING;
	ifstream iFile_INTVSFLOAT;
	ifstream iFile_INTVSOBJECT;


	char* check_report_set;


	STATUS result;


	int no_of_entries;



	while(1)
	{
		cout<<"Select from the options\n";
		cout<<" NOTE: Please set the env variable to obtain the Output Report\n 1------ <KEY(int), VALUE(int)> type HASHMAP\n 2------ <KEY(int), VALUE(string)> type HASHMAP\n 3------ <KEY(int), VALUE(float)> type HASHMAP\n 4------ <KEY(int), VALUE(object)>type HASHMAP\n 5------ Destruct\n 6------ Iterator traving of IntvsInt \n 7------ Collision per slot for IntvsFloat\n\n";
		cin>>choice;

		switch(choice)
		{
			case INTvsINT:
			{

				cout<<"Enter the no. of entries you need to make\n";
				cin>>no_of_entries;
				Time_Set time_obj_ivsi;
				keyInputIntvsInt = start_key_all;
				valInputIntvsInt = start_val_int;
				for(int j=0;j<no_of_entries;j++)
				{
					result = objIntvsInt.findAndInsert(keyInputIntvsInt, valInputIntvsInt);
					keyInputIntvsInt += offset_key_all;
					valInputIntvsInt += offset_val_int_string;
					if(result == SUCCESS)
						cout<<"Inserted Successfully\n";
					else if(result == DUP_KEY)
						cout<<"Duplicate Key\n Please enter the Different key-value Par\n";
					else
						cout<<"MEMory allocation failes\n";
				}
				double return_time_end =(-1) * time_obj_ivsi.clock_end();

				check_report_set = getenv ("SET_REPORT");
				  if (check_report_set!=NULL)
				  {
					  cout<<"value is "<<check_report_set;
					ofstream fileOutput_INTVSINT;
					fileOutput_INTVSINT.open("C:\\Users\\murthk5\\Desktop\\statistics.txt",std::ios_base::app);

					fileOutput_INTVSINT<<"Showing the Statistics for HASHMAP<INT, INT> of size "<<MAX_SPACE<<"\n";

					fileOutput_INTVSINT<<"\t\tThe No. of entries in the Hash Table is "<<objIntvsInt.size()<<"\n";

					fileOutput_INTVSINT<<"\t\tThe total no. of collisons happened was "<<objIntvsInt.getTotalNumberOfCollision()<<"\n";

					fileOutput_INTVSINT<<"\t\tSUMMARY OF THE HASH TABLE"<<"\n";

					uint32_t* collStat_INTVSINT = objIntvsInt.printCollisionStatistics();

					fileOutput_INTVSINT<<"\t\tSlot							Collision\n\n\n";
					for(int i=0;i<MAX_SPACE;i++)
					{
						fileOutput_INTVSINT<<"\t\t"<<i<<"							"<<collStat_INTVSINT[i]<<"\n";

					}

					fileOutput_INTVSINT << "It took me " << return_time_end << " units of time for"<<objIntvsInt.size()<<"entries"<<"\n";
					fileOutput_INTVSINT<<"\n\n\n\n";
				  }

				  for(int i=start_key_all;i<10000;i+=(offset_key_all*2))
				  {
					  if(objIntvsInt.remove(i))
						  cout<<i<<" is Removed Successfully\n";
					  else
						  cout<<"Key not found";
				  }


					break;
				}

		case INTvsSTRING:	{
			cout<<"Enter the no. of entries you need to make\n";
			cin>>no_of_entries;
			Time_Set time_obj_ivss;
			keyInputIntvsString = start_key_all;
			valInputIntvsString = start_val_string;
			int temp_offset = offset_val_int_string;


			for(int j=0;j<no_of_entries;j++)
			{
				result = objIntvsString.findAndInsert(keyInputIntvsString, valInputIntvsString);
				keyInputIntvsString += offset_key_all;
				valInputIntvsString = start_val_string;
				temp_offset++;
				valInputIntvsString.append(std::to_string(temp_offset));
				if(result == SUCCESS)
						cout<<"Inserted Successfully\n";
				else if(result == DUP_KEY)
					cout<<"Duplicate Key\n Please enter the Different key-value Par\n";
				else
					cout<<"MEMory allocation failes\n";
			}
			double return_time_end =(-1) * time_obj_ivss.clock_end();

			check_report_set = getenv ("SET_REPORT");
			if (check_report_set!=NULL)
			{


				ofstream fileOutput_INTVSSTRING;
				fileOutput_INTVSSTRING.open("C:\\Users\\murthk5\\Desktop\\statistics.txt",std::ios_base::app);

				fileOutput_INTVSSTRING<<"Showing the Statistics for HASHMAP<INT, STRING> of size "<<MAX_SPACE<<"\n";

				fileOutput_INTVSSTRING<<"The No. of entries in the Hash Table is "<<objIntvsString.size()<<std::endl;

				fileOutput_INTVSSTRING<<"The total no. of collisons happened was "<<objIntvsString.getTotalNumberOfCollision()<<"\n";

				fileOutput_INTVSSTRING<<"\t\tSUMMARY OF THE HASH TABLE"<<"\n";

				uint32_t* collStat_INTVSSTRING = objIntvsString.printCollisionStatistics();

				fileOutput_INTVSSTRING<<"\t\tSlot							Collision\n\n\n";
				for(int i=0;i<MAX_SPACE;i++)
				{
					fileOutput_INTVSSTRING<<"\t\t"<<i<<"							"<<collStat_INTVSSTRING[i]<<"\n";

				}

				fileOutput_INTVSSTRING << "It took me " << return_time_end << " nseconds for"<<objIntvsString.size()<<"entries"<<"\n";
				fileOutput_INTVSSTRING<<"\n\n\n\n";

			}
						break;

		}
		case INTvsFLOAT:
		{
						cout<<"Enter the no. of entries you need to make\n";
						Time_Set time_obj_ivsf;
						cin>>no_of_entries;
						keyInputIntvsFloat = start_key_all;
						valInputIntvsFloat = start_val_int;
						for(int j=0;j<no_of_entries;j++)
						{
							result = objIntvsFloat.findAndInsert(keyInputIntvsFloat, valInputIntvsFloat);
							keyInputIntvsFloat += offset_key_all;
							valInputIntvsFloat += offset_val_float;
							if(result == SUCCESS)
								cout<<"Inserted Successfully\n";
							else if(result == DUP_KEY)
								cout<<"Duplicate Key\n Please enter the Different key-value Par\n";
							else
								cout<<"MEMory allocation failes\n";
						}
						double return_time_end = (-1) * time_obj_ivsf.clock_end();

						check_report_set = getenv ("SET_REPORT");
						if (check_report_set!=NULL)
						{


							ofstream fileOutput_INTVSFLOAT;
							fileOutput_INTVSFLOAT.open("C:\\Users\\murthk5\\Desktop\\statistics.txt",std::ios_base::app);

							fileOutput_INTVSFLOAT<<"Showing the Statistics for HASHMAP<INT, FLOAT> of size "<<MAX_SPACE<<"\n";

							fileOutput_INTVSFLOAT<<"The No. of entries in the Hash Table is \n "<<objIntvsFloat.size()<<std::endl;

							fileOutput_INTVSFLOAT<<"The total no. of collisons happened was "<<objIntvsFloat.getTotalNumberOfCollision()<<"\n";

							fileOutput_INTVSFLOAT<<"\t\tSUMMARY OF THE HASH TABLE"<<"\n";

							uint32_t* collStat_INTVSFLOAT = objIntvsFloat.printCollisionStatistics();

							fileOutput_INTVSFLOAT<<"\t\tSlot							Collision\n\n\n";
							for(int i=0;i<MAX_SPACE;i++)
							{
								fileOutput_INTVSFLOAT<<"\t\t"<<i<<"							"<<collStat_INTVSFLOAT[i]<<"\n";

							}
							fileOutput_INTVSFLOAT << "It took me " <<return_time_end << " nseconds for"<<objIntvsFloat.size()<<"entries"<<"\n";
							fileOutput_INTVSFLOAT<<"\n\n\n\n";

						}
						break;
		}

		case INTvsOBJECT:
		{

			cout<<"Enter the no. of entries you need to make\n";
			cin>>no_of_entries;
			Time_Set time_obj_ivso;
			keyInputIntvsObject = start_key_all;

			stu.name=start_val_string;
			stu.age=start_val_age;
			stu.marks=start_val_marks;
			int temp_offset = offset_val_int_string;
			for(int j=0;j<no_of_entries;j++)
			{
				result = objIntvsObject.findAndInsert(keyInputIntvsObject, stu);
				keyInputIntvsObject += offset_key_all;


				stu.name = start_val_string;
				temp_offset++;
				stu.name.append(std::to_string(temp_offset));
				stu.age += offset_val_int_string;
				stu.marks += offset_val_int_string;

				if(result == SUCCESS)
					cout<<"Inserted Successfully\n";
				else if(result == DUP_KEY)
					cout<<"Duplicate Key\n Please enter the Different key-value Par\n";
				else
					cout<<"MEMory allocation failes\n";
			}
			double return_time_end = (-1) * time_obj_ivso.clock_end();

			check_report_set = getenv ("SET_REPORT");
			if (check_report_set!=NULL)
			{


				ofstream fileOutput_INTVSOBJECT;
				fileOutput_INTVSOBJECT.open("C:\\Users\\murthk5\\Desktop\\statistics.txt",std::ios_base::app);
				fileOutput_INTVSOBJECT<<"Showing the Statistics for HASHMAP<INT, OBJECT> of size "<<MAX_SPACE<<"\n";

				fileOutput_INTVSOBJECT<<"The No. of entries of the Hash Table is \n "<<objIntvsObject.size()<<std::endl;

				fileOutput_INTVSOBJECT<<"The total no. of collisons happened was "<<objIntvsObject.getTotalNumberOfCollision()<<"\n";

				fileOutput_INTVSOBJECT<<"\t\tSUMMARY OF THE HASH TABLE"<<"\n";

				uint32_t* collStat_INTVSOBJECT = objIntvsObject.printCollisionStatistics();

				fileOutput_INTVSOBJECT<<"\t\tSlot							Collision\n\n\n";
				for(int i=0;i<MAX_SPACE;i++)
				{
					fileOutput_INTVSOBJECT<<"\t\t"<<i<<"							"<<collStat_INTVSOBJECT[i]<<"\n";

				}

				fileOutput_INTVSOBJECT << "It took me " <<return_time_end  << " nseconds for"<<objIntvsObject.size()<<"entries"<<"\n";
				fileOutput_INTVSOBJECT<<"\n\n\n\n";
			}

			break;
		}
		case DESTRUCT_EXPLICIT:		{
						objIntvsInt.~MyHashmap();
						objIntvsString.~MyHashmap();
						objIntvsFloat.~MyHashmap();
						objIntvsObject.~MyHashmap();
						//break;
						exit(0);
		}
		case ITERATORINTVSINT:	{

			int x=0;

			for(MyHashmap<int, int>::ForwardIter itrtest=objIntvsInt.begin();itrtest!=objIntvsInt.end();++itrtest)
								{
									cout<<*itrtest<<"\n";

								}

					break;
		}

		case COLLISION_INTVSFLOAT_AT_SLOT:
		{
			cout<<"Enter the slot Number to find the collision\n";
			cin>>slotNumber;
			slotCollis = objIntvsFloat.getNumberOfCollisionPerSlot(slotNumber);
			cout<<"The total no. of collisons happened at 	slot "<<slotNumber<<" is "<<slotCollis;

			break;
		}

		default: cout<<"Enter the correct choice\n";
					break;

		}
	}

		//cout<<"Enter the keyn and the value";
		//cin>>keyInput;
	//getline(cin,valInput);


	return 0;
}



