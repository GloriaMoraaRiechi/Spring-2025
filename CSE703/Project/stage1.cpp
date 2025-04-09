#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue> // For priority_queue
#include <string>

using namespace std;

// Struct to store patient data with an added 'Stage' field (int)
struct CKD_Patient {
    int PatientID;
    int Age;
    int Gender;
    int SocioeconomicStatus;
    int EducationLevel;
    double BMI;
    int Smoking;
    double AlcoholConsumption;
    double DietQuality;
    double SleepQuality;
    int FamilyHistoryKidneyDisease;
    int FamilyHistoryHypertension;
    int FamilyHistoryDiabetes;
    int PreviousAcuteKidneyInjury;
    int UrinaryTractInfections;
    int SystolicBP;
    int DiastolicBP;
    double FastingBloodSugar;
    double HbA1c;
    double SerumCreatinine;
    double BUNLevels;
    double GFR;
    double ProteinInUrine;
    double ACR;
    double SerumElectrolytesSodium;
    double SerumElectrolytesPotassium;
    double SerumElectrolytesCalcium;
    double SerumElectrolytesPhosphorus;
    double HemoglobinLevels;
    double CholesterolTotal;
    double CholesterolLDL;
    double CholesterolHDL;
    double CholesterolTriglycerides;
    int ACEInhibitors;
    int Diuretics;
    int NSAIDsUse;
    int Statins;
    int AntidiabeticMedications;
    int Edema;
    int FatigueLevels;
    int NauseaVomiting;
    int MuscleCramps;
    int Itching;
    double QualityOfLifeScore;
    int HeavyMetalsExposure;
    int OccupationalExposureChemicals;
    int WaterQuality;
    int MedicalCheckupsFrequency;
    int MedicationAdherence;
    int HealthLiteracy;
    int Diagnosis;
    int Stage;  // Changed field for CKD Stage (int)
};

// Comparator for priority_queue to create a min-heap based on GFR
struct CompareGFR {
    bool operator()(const CKD_Patient& p1, const CKD_Patient& p2) {
        return p1.GFR > p2.GFR; // Min-heap based on GFR (lowest GFR at root)
    }
};

int main() {
        string file_path = "/mnt/c/Users/glori/Desktop/Program for Scalable Computing/updated_CKD_data1.csv"; 

    ifstream file(file_path);
    string line;

    if (!file.is_open()) {
        cerr << "Could not open the file!" << endl;
        return -1;
    }

    priority_queue<CKD_Patient, vector<CKD_Patient>, CompareGFR> patientHeap;

    bool is_header = true;

    while (getline(file, line)) {
        if (is_header) {
            is_header = false;  // Skip header
            continue;
        }

        stringstream ss(line);
        string value;
        CKD_Patient patient;

        // Read CSV values and assign to patient structure
        getline(ss, value, ','); patient.PatientID = stoi(value);
        getline(ss, value, ','); patient.Age = stoi(value);
        getline(ss, value, ','); patient.Gender = stoi(value);
        getline(ss, value, ','); patient.SocioeconomicStatus = stoi(value);
        getline(ss, value, ','); patient.EducationLevel = stoi(value);
        getline(ss, value, ','); patient.BMI = stod(value);
        getline(ss, value, ','); patient.Smoking = stoi(value);
        getline(ss, value, ','); patient.AlcoholConsumption = stod(value);
        getline(ss, value, ','); patient.DietQuality = stod(value);
        getline(ss, value, ','); patient.SleepQuality = stod(value);
        getline(ss, value, ','); patient.FamilyHistoryKidneyDisease = stoi(value);
        getline(ss, value, ','); patient.FamilyHistoryHypertension = stoi(value);
        getline(ss, value, ','); patient.FamilyHistoryDiabetes = stoi(value);
        getline(ss, value, ','); patient.PreviousAcuteKidneyInjury = stoi(value);
        getline(ss, value, ','); patient.UrinaryTractInfections = stoi(value);
        getline(ss, value, ','); patient.SystolicBP = stoi(value);
        getline(ss, value, ','); patient.DiastolicBP = stoi(value);
        getline(ss, value, ','); patient.FastingBloodSugar = stod(value);
        getline(ss, value, ','); patient.HbA1c = stod(value);
        getline(ss, value, ','); patient.SerumCreatinine = stod(value);
        getline(ss, value, ','); patient.BUNLevels = stod(value);
        getline(ss, value, ','); patient.GFR = stod(value); // This will determine heap placement
        getline(ss, value, ','); patient.ProteinInUrine = stod(value);
        getline(ss, value, ','); patient.ACR = stod(value);
        getline(ss, value, ','); patient.SerumElectrolytesSodium = stod(value);
        getline(ss, value, ','); patient.SerumElectrolytesPotassium = stod(value);
        getline(ss, value, ','); patient.SerumElectrolytesCalcium = stod(value);
        getline(ss, value, ','); patient.SerumElectrolytesPhosphorus = stod(value);
        getline(ss, value, ','); patient.HemoglobinLevels = stod(value);
        getline(ss, value, ','); patient.CholesterolTotal = stod(value);
        getline(ss, value, ','); patient.CholesterolLDL = stod(value);
        getline(ss, value, ','); patient.CholesterolHDL = stod(value);
        getline(ss, value, ','); patient.CholesterolTriglycerides = stod(value);
        getline(ss, value, ','); patient.ACEInhibitors = stoi(value);
        getline(ss, value, ','); patient.Diuretics = stoi(value);
        getline(ss, value, ','); patient.NSAIDsUse = stoi(value);
        getline(ss, value, ','); patient.Statins = stoi(value);
        getline(ss, value, ','); patient.AntidiabeticMedications = stoi(value);
        getline(ss, value, ','); patient.Edema = stoi(value);
        getline(ss, value, ','); patient.FatigueLevels = stoi(value);
        getline(ss, value, ','); patient.NauseaVomiting = stoi(value);
        getline(ss, value, ','); patient.MuscleCramps = stoi(value);
        getline(ss, value, ','); patient.Itching = stoi(value);
        getline(ss, value, ','); patient.QualityOfLifeScore = stod(value);
        getline(ss, value, ','); patient.HeavyMetalsExposure = stoi(value);
        getline(ss, value, ','); patient.OccupationalExposureChemicals = stoi(value);
        getline(ss, value, ','); patient.WaterQuality = stoi(value);
        getline(ss, value, ','); patient.MedicalCheckupsFrequency = stoi(value);
        getline(ss, value, ','); patient.MedicationAdherence = stoi(value);
        getline(ss, value, ','); patient.HealthLiteracy = stoi(value);
        getline(ss, value, ','); patient.Diagnosis = stoi(value);
        getline(ss, value, ','); patient.Stage = stoi(value);  // Directly read Stage from dataset

        // Push patient into the heap
        patientHeap.push(patient);
    }

    file.close();

    // Print out the top patient from the heap (the one with the lowest GFR)
    if (!patientHeap.empty()) {
        CKD_Patient patient = patientHeap.top();
        cout << "Patient with lowest GFR: " << endl;
        cout << "PatientID: " << patient.PatientID << " | Age: " << patient.Age << " | GFR: " << patient.GFR 
             << " | Stage: " << patient.Stage << endl;
    }

    return 0;
}

