//Header file - For class Cluster
//Defines a data Structure for storin information on clusters

//Dependencies ==> 
//				  

//Status - Incomplete, Not tested
//Author - yatharthb97


#include <iostream>
#include <vector>
#include <algorithm>

class Cluster
{
public:
	//Member Variables

	int ClustID;
	bool active;
	int ClustPartCount;
	std::vector<double> ClustPartList;


	Cluster(int ClustID): ClustID(ClustID), ClustPartCount(0), active(true) 
	{
		cout<<"Cluster created with ClustID: "<<ClustID<<endl;
	}


	void clustadd(int partid)
	{
		ClustPartList.push_back(partid);
		ClustPartCount++;
	}


	void ClustPartListSort()
	{
		 sort(this->ClustPartList.begin(), this->ClustPartList.end());
		 cout<<"Sorted Cluster Particle List with ClustID: "<<ClustID<<endl;

	}

	void CopyClust(Cluster &other)
	{
		 
		 int TempSize = this->ClustPartCount;
		 //other.ClustPartListSort(); //Sort the other Cluster Particle List
		//ClustPartListSort(); //Sort Current Cluster Particle List
		for(unsigned int i = 0; i < other.ClustPartCount; i++)
		{
			//Make Changes to the current cluster
			this->ClustPartList.push_back(other.ClustPartList.at(i));
			this->ClustPartCount++;

			//Make changes to the individual particle
			partlist(other.ClustPartList.at(i)).clusterSwitch = true;
			partlist(other.ClustPartList.at(i)).clusterID = this->ClustID;
			
		}

		if(this->ClustPartCount != (other.ClustPartCount + TempSize))
		{
			cerr<<"Cluster copy failure!"<<endl; 
		}

		else
		{
			ClustPartListSort(); //Sort Current Cluster Particle List
			cout<<"Cluster Copy successful!"<<endl;
		}

	}

	void BinCluster()
	{
		active = false;
		ClustPartList.clear();
		ClustPartCount = ClustPartCount.size();
		cout<<"Cluster ID binned: "<<ClustID<<" Size: "<<ClustPartCount<<endl; //Check if the vector is properly cleared.	
	}


	~Cluster()
	{
		cout<<"The Cluster Destructor is called for ClustID: "<<ClustID;

	}


};