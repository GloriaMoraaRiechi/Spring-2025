#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue> // For priority_queue
#include <string>
#include <omp.h> // OpenMP header
#include <algorithm>

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

// Simulate disease progression based on various factors
void simulate_event(CKD_Patient& patient, double time_step) {
    // Simulate GFR decline with age progression
    if (time_step >= 1.0) {  // Assuming yearly progression
        // Base GFR decline rate: 5 GFR per year
        patient.GFR -= 5;

        // Influence of medications
        if (patient.ACEInhibitors) {
            patient.GFR -= 2; // ACE inhibitors may slow the progression (slightly)
        }
        if (patient.Diuretics) {
            patient.GFR -= 1; // Diuretics might help stabilize GFR
        }
        if (patient.Statins) {
            patient.GFR -= 1; // Statins may reduce cardiovascular risks that affect CKD progression
        }

        // Influence of lifestyle factors
        if (patient.Smoking) {
            patient.GFR -= 2; // Smoking accelerates CKD progression
        }
        if (patient.BMI > 30) {  // BMI above 30 is considered obese
            patient.GFR -= 2; // Obesity worsens CKD
        }

        // Influence of comorbidities
        if (patient.FamilyHistoryKidneyDisease) {
            patient.GFR -= 1; // Family history may accelerate progression
        }
        if (patient.FamilyHistoryHypertension) {
            patient.GFR -= 1; // Hypertension exacerbates CKD
        }
        if (patient.FamilyHistoryDiabetes) {
            patient.GFR -= 2; // Diabetes increases the rate of CKD progression
        }

        // Other factors: Age-related decline, other medical events
        patient.GFR -= 0.5;  // General decline due to aging
        if (patient.GFR < 15) {
            patient.Stage = 5; // End-stage renal failure (Stage 5)
        } else if (patient.GFR < 30) {
            patient.Stage = 4; // Stage 4 CKD
        } else if (patient.GFR < 60) {
            patient.Stage = 3; // Stage 3 CKD
        } else if (patient.GFR < 90) {
            patient.Stage = 2; // Stage 2 CKD
        } else {
            patient.Stage = 1; // Stage 1 CKD
        }
    }
}

// Simulate disease progression for a list of patients
void simulate_for_patients(vector<CKD_Patient>& patients, double time_step) {
    // Parallelize using OpenMP to process each patient in parallel
    #pragma omp parallel for
    for (int i = 0; i < patients.size(); i++) {
        simulate_event(patients[i], time_step);
    }
}

// Function to load patients from CSV
void load_patients(string file_path, vector<CKD_Patient>& patients) {
    ifstream file(file_path);
    string line;
    bool is_header = true;

    while (getline(file, line)) {
        if (is_header) {
            is_header = false;
            continue;
        }

        stringstream ss(line);
        string value;
        CKD_Patient patient;

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
        getline(ss, value, ','); patient.GFR = stod(value);
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

        patients.push_back(patient);
    }

    file.close();
}

int main() {
    string file_path = "/mnt/c/Users/glori/Desktop/Program for Scalable Computing/updated_CKD_data1.csv";
    vector<CKD_Patient> patients;

    // Load patients from CSV
    load_patients(file_path, patients);

    double time_step = 1.0;  // Simulate yearly progression

    // Simulate disease progression for each patient
    simulate_for_patients(patients, time_step);

    // Print out the updated patient with lowest GFR
    if (!patients.empty()) {
        CKD_Patient lowest_GFR_patient = *min_element(patients.begin(), patients.end(),
                                                      [](const CKD_Patient& a, const CKD_Patient& b) {
                                                          return a.GFR < b.GFR;
                                                      });
        cout << "Patient with lowest GFR after progression: " << endl;
        cout << "PatientID: " << lowest_GFR_patient.PatientID << " | Age: " << lowest_GFR_patient.Age
             << " | GFR: " << lowest_GFR_patient.GFR << " | Stage: " << lowest_GFR_patient.Stage << endl;
    }

    return 0;
}
