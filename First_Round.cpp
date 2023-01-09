#include <iostream>
#include <json/json.h> // Source : https://github.com/open-source-parsers/jsoncpp
#include <fstream>

using namespace std;

void Skipline(int n)
{
	//this method take a number, verify if it's divisble by 4, 9 or both and display line according to the result.
	for (int i = 1; i <= n; i++) {
		int fourth = i % 4, ninth = i % 9;
		if ((fourth == 0) && (ninth == 0))
		{
			cout << "SkipLine \n";
		}
		else if (fourth == 0)
		{
			cout << "Skip \n";
		}
		else if (ninth == 0)
		{
			cout << "Line \n" ;
		}
		else
		{
			cout << i << "\n";
		}
	}
}

vector <Json::Value> compare(Json::Value L1, Json::Value L2, string jsonname)
{
	//This method is use to compare data from one Json file with the other Json file, save missing information and return the missing value.
	vector <Json::Value> Temparray;

	for (Json::ArrayIndex i = 0; i < L1.size(); i++)
	{
		for (Json::ArrayIndex j = 0; j < L1[i]["enums"].size(); j++)
		{
			for (Json::ArrayIndex u = 0; u < L2.size(); u++)
			{
				if (L2[u]["enum"] == L1[i]["enums"][j]["name"])
				{
					break;
				}
				else if (u == (L2.size() - 1))
				{
					Temparray.push_back(L1[i]["enums"][j]["name"]);
					Temparray.push_back(L1[i]["name"]);
					Temparray.push_back(jsonname);
				}
			}
		}
	}
	return Temparray;
}

Json::Value initjson(string filename)
{
	//this method initialize and save the data contain in the Json file.
	ifstream root(filename); //open file
	Json::Value Data; //contain the complete Json data
	Json::Reader Read;
	Read.parse(root, Data, false);// Read the Json file and store it into the Data file

	return Data;
}

void Check_up()
{

	//this method take in the Json parse the Json, call the compare method and combine all the data retrived from the compare method and display it to the user.

	Json::Value Data = initjson("master_enum.json");
	Json::Value Data_DE = initjson("lang_de.json");
	Json::Value Data_EN = initjson("lang_en-us.json");
	Json::Value Data_ES = initjson("lang_es.json");
	Json::Value Data_FR = initjson("lang_fr.json");
	
	vector<Json::Value> Missing;
	vector<Json::Value> tempDE = compare(Data, Data_DE, "lang_de.json");
	vector<Json::Value> tempEN = compare(Data, Data_EN, "lang_en-us.json");
	vector<Json::Value> tempES = compare(Data, Data_ES, "lang_es.json");
	vector<Json::Value> tempFR = compare(Data, Data_FR, "lang_fr.json");

	Missing.insert(Missing.end(), tempDE.begin(), tempDE.end());
	Missing.insert(Missing.end(), tempEN.begin(), tempEN.end());
	Missing.insert(Missing.end(), tempES.begin(), tempES.end());
	Missing.insert(Missing.end(), tempFR.begin(), tempFR.end()); //Add all Json into one document for display purpose.
	

	for (int i = 0; i < Missing.size(); i++)
	{
		cout << Missing[i] << "\t";
		if (((i + 1)% 3) == 0)
		{
			cout << endl;
		}
	}
}

int main()
{

	struct Datapacket
	{
		int32_t id;
		int32_t timestamp;
		uint8_t data;
		uint8_t len;
	};
	printf("%u\n", sizeof(Datapacket));
	//Skipline(100);
	//Check_up();
	return 0;
}