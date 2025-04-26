#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>

using namespace std;

string playerName;

class SubCategories
{
    private:
        string category;
        string difficulty;
        int pointPerDifficulty;

    public:
        SubCategories() {}
        SubCategories(string category, string difficulty, int pointPerDifficulty)
        : category(category), difficulty(difficulty), pointPerDifficulty(pointPerDifficulty) {}

        string getCategory() { return category; }
        string getDifficulty() { return difficulty; }
        int getPointPerDifficulty() { return pointPerDifficulty; }
};

class Question
{
    private:
        string questionText;
        string options;
        SubCategories subCategories;        
        int correctOption;

    public:
        Question(){}
        Question(string questionText, string options, SubCategories subCategories, int correctOption) : 
        questionText(questionText), options(options), subCategories(subCategories), correctOption(correctOption) {}

        string getQuestionText() { return questionText; }
        string getOptions() { cout << endl ; return options; }

        void askQuestion()
        {
            cout << questionText << endl;
            cout << options << endl;
        }

        string getCategory() { getSubCategories().getCategory(); }
        string getDifficulty() { getSubCategories().getDifficulty(); }
        int getPointPerDifficulty() { getSubCategories().getPointPerDifficulty(); }

        SubCategories getSubCategories() {return subCategories; }
        int getCorrectOption() { return correctOption; }

};

class ScoreCollector : public Question
{
    private:
        int score = 0;
        int totalScore;
        int totalEasyScore = 5;
        int totalMediumScore = 10;
        int totalHardScore = 25;
        SubCategories subCategories;

    public:

        ScoreCollector() {}
        ScoreCollector(SubCategories subCategories): subCategories(subCategories) {};

        SubCategories getSubCategories() { return subCategories; }

        int getTotalEasyScore() { return totalEasyScore; }
        int getTotalMediumScore() { return totalMediumScore; }
        int getTotalHardScore() { return totalHardScore; }



        int getTotalScore()
        {
            if (subCategories.getDifficulty() == "easy") {
                return totalEasyScore;
            } else if (subCategories.getDifficulty() == "medium") {
                return totalMediumScore;
            } else {
                return totalHardScore;
            }
        }

        int optionValidator(int choice)
        {
            while(true) 
            {
                if(choice)
                {
                    if(choice >= 1 && choice <= 4) 
                    {
                        return choice;
                    } 
                    else
                    {
                        cout << "Please enter a number between 1 and 4.\n";
                    }
                } 
                else
                {
                    cout << "Invalid input. Please enter a valid option.\n";
                    while(cin.get() != '\n');
                }
            }
        }


        void updateScore()
        {
            int points = subCategories.getPointPerDifficulty();
            score += points;
        }

        void displayScore()
        {
            cout<<"Your score is: " << score << "/" << getTotalScore() << endl;
            char ch = _getch();
        }

        void updateLeaderboard(string playerName)
        {
            ofstream leaderFile("leaderboard.txt", ios::app);

            if (!leaderFile)
            {
                cout << "Failed to open the Leaderboard..." << endl;
                return;
            }
            
           
            leaderFile << "*  " << playerName << " has Scored " << score << " out of "  <<getTotalScore()<< " in '" << getSubCategories().getCategory() << "' category " << " at '" << getSubCategories().getDifficulty() << "' difficulty." << endl;
            
            leaderFile.close();
        }

        void updateIndividualFile(string playerName)
        {
            ofstream individualfile(playerName, ios::app);

            if(!individualfile)
            {
                cout<< "Failed to open the file. Creating new one." << endl;
                individualfile.open(playerName);
            }

            cin.ignore();
            individualfile << playerName << " has scored " << score << " out of " << getTotalScore() << " in '" << subCategories.getCategory() << "' category " << " at '" << subCategories.getDifficulty() << "' difficulty." << endl;
        }

        void updateIndividualcsvFile(string playerName)
        {
            ofstream individualcsvFile(playerName + ".csv", ios::app);

            if(!individualcsvFile)
            {
                cout<< "Failed to open the file. Creating new one." << endl;
                individualcsvFile.open(playerName + ".csv");                
            }

//            cin.ignore();
            string data = playerName + "," + to_string(score) + "," + to_string(getTotalScore()) + "," + subCategories.getCategory() + "," + subCategories.getDifficulty();
            individualcsvFile << data << endl;
        }

        void updateIndividualBinaryFile(string playerName)
        {
            ofstream individualBinaryFile(playerName + ".bin", ios::binary | ios::app);
            
            if(!individualBinaryFile)
            {
                cout<< "Failed to open the file. Creating new one." << endl;
                individualBinaryFile.open(playerName + ".bin");                
            }

            string data = playerName + " has scored " + to_string(score) + " out of " + to_string(getTotalScore()) + " in '" + subCategories.getCategory() + "' category at '" + subCategories.getDifficulty() + "' difficulty.";
            individualBinaryFile.write(data.c_str(), data.size());
            individualBinaryFile.close();
        
        }





        ~ScoreCollector() {}
};

        void showLeaderboard()
        {
            ifstream leaderfile("leaderboard.txt");
            if(!leaderfile)
            {
                cout<<"ERROR! the file cannot be opened...\n";
                return;
            }
            string content;
            while(getline(leaderfile, content))
            {
                cout << content << endl;
            }
            leaderfile.close();
            cout << endl;
            cout << "Press any Key to continue...";
            char ch = _getch();
        }

        void showIndividualScore()
        {
            ifstream individualFile(playerName);
            if(!individualFile.is_open())
            {
                cout<<"ERROR! the file cannot be opened...\n";
                return;
            }
            string content;
            while(getline(individualFile, content))
            {
                cout << content << endl;
            }
            individualFile.close();
            cout << endl;
            cout << "Press any Key to continue...";
            char ch = _getch();
        }

        void showIndividualCsv()
        {
            ifstream individualFile(playerName + ".csv");
            if(!individualFile.is_open())
            {
                cout<<"ERROR! the file cannot be opened...\n";
                return;
            }
            string content;
            while(getline(individualFile, content))
            {
                cout << content << endl;
            }
            individualFile.close();
            cout << endl;
            cout << "Press any Key to continue...";
            char ch = _getch();
        }

        void showIndividualBinary()
        {
            ifstream individualFile(playerName + ".bin");
            if(!individualFile.is_open())
            {
                cout<<"ERROR! the file cannot be opened...\n";
                return;
            }
            string content;
            while(getline(individualFile, content))
            {
                cout << content << endl;
            }
            individualFile.close();
            cout << endl;
            cout << "Press any Key to continue...";
            char ch = _getch();
        }

int inputValidation(string prompt, int choice)
{
    while (true)
    {
        cout << prompt;
        if (cin >> choice)
        {
            return choice;
        } 
        else 
        {
            cout << "Invalid input. Please enter a valid number.\n";
            cin.clear();
            cin.ignore(132, '\n');
        }
    }
}
    int questionChoice;
    int mainMenuChoice;
    int categoryChoice;
    int difficultyChoice;
    int scoreChoice;


void welcome()
{
            ifstream myfile("WELCOME.txt");
            if(!myfile)
            {
                cout<<"ERROR! the file cannot be opened...\n";
                return;
            }
            string content;
            while(getline(myfile, content))
            {
                cout << content <<endl;
            }
            myfile.close();

            cout << endl;
            cout << "Press any Key to continue...";
            char ch = _getch();

}

int main()
{   
    SubCategories historyEasy("history", "easy", 1);
    SubCategories historyMedium("history", "medium", 2);
    SubCategories historyHard("history", "hard", 5);
    
    SubCategories geographyEasy("geography", "easy", 1);
    SubCategories geographyMedium("geography", "medium", 2);
    SubCategories geographyHard("geography", "hard", 5);

    SubCategories CSEasy("CS", "easy", 1);
    SubCategories CSMedium("CS", "medium", 2);
    SubCategories CSHard("CS", "hard", 5);

    SubCategories scienceEasy("science", "easy", 1);
    SubCategories scienceMedium("science", "medium", 2);
    SubCategories scienceHard("science", "hard", 5);


    ScoreCollector HE(historyEasy);
    ScoreCollector HM(historyMedium);
    ScoreCollector HH(historyHard);
    
    ScoreCollector GE(geographyEasy);
    ScoreCollector GM(geographyMedium);
    ScoreCollector GH(geographyHard);

    ScoreCollector CE(CSEasy);
    ScoreCollector CM(CSMedium);
    ScoreCollector CH(CSHard);

    ScoreCollector SE(scienceEasy);
    ScoreCollector SM(scienceMedium);
    ScoreCollector SH(scienceHard);


    Question ehistoryQuestion[5] = {
    Question("Who was the first Prime Minister of the Pakistan?", "1.Quaid-e-Azam    2.Iskander Mirza    3.Liaqat Ali Khan    4.I. I. Chundrigar", historyEasy, 3),
    Question("Which ancient civilization built the Great Pyramids of Giza?", "1.Assysian civilization   2.Persian civilization   3.Egyptian civilization   4.Indus civilization", historyEasy, 3),
    Question("Who was the first CIVIL Martial Law Administrator of Pakistan?", "1.Ayub Khan    2.Zulfiqar Ali Bhutto    3.Yahya Khan    4.Mujeeb ur Rahman", historyEasy, 2),
    Question("In which year did the Indian Rebbellion take place?", "1.1857    2.1847    3.1877    4.1897", historyEasy, 1),
    Question("Who was the founder of the terrorist organization 'Al-Qaeda'?", "1.Abu Bakr AL-Baghdadi    2.Osama bin Ladin    3.Mullah Omar    4.Mullah Arslan Arsal", historyEasy, 2)
    };

    Question mhistoryQuestion[5] = {
    Question("Which event marked the beginning of World War II?", "1.Invasian of Poland    2.Invasian of Czech Republic    3.Attack of Pearl Harbor    4.Invasian of France", historyMedium, 1),
    Question("Which event marked the beginning of World War I?", "1.Invasian of Serbia    2.Assassination of Franz Ferdinand    3.Invasian of Russia    4.the Arab Revolt", historyMedium, 2),
    Question("The famous 'I Have a Dream' speech was delivered by which civil rights leader?", "1.Nelson Mendela    2.Mahatma Gandhi    3.Martin Luther King jr.    4.Chaudhry Rehmat Ali", historyMedium, 3),
    Question("What was the capital of ASSYRIAN EMPIRE?", "1.Babylon    2.Thebes    3.Sparta    4.Ninevah", historyMedium, 4),
    Question("Alexander the Great faced whom at the battle of Hydaspes?", "1.Darius III    2.Seti I    3.Maharaja Porus    4.Ptolemy", historyMedium, 3)
    };

    Question hhistoryQuestion[5] = {
    Question("In which year did Christopher Columbus first reach the Americas?", "1.1492    2.1490    3.1515    4.1480", historyHard, 1),
    Question("Who formed the BOLSHEVIK movement in Imperial Russia?", "1.Joseph Stalin    2.Vladimir Lenin    3.Adolph Hitler    4.Czar Nicholas", historyHard, 2),
    Question("Who formed the society 'Nation of Islam' in USA?", "1.Elijah Muhammad    2.Malcolm X    3.Fard Muhammad    4.Muhammad Ali", historyHard, 3),
    Question("Who was the founder of the FIRST PERSIAN EMPIRE?", "1.Alexander the Great    2.Ivan the Terrible    3.Cyrus the Great    4.Nicholas the Great", historyHard, 3),
    Question("Who was the president of the USA during the Civil War?", "1.John Adams    2.Teddy Roosevelt    3.George Washington    4.Abraham Lincoln", historyHard, 3)
    };



    Question egeographyQuestion[5] = {
    Question("Which coastal city is known as 'city of lights' in pakistan?", "1.Karachi    2.Lahore    3.Mandi Bahauddin    4.Gwadar", geographyEasy, 1),
    Question("What mountain range forms the northern border of Pakistan?", "1.Alps    2.Himalayas    3.HinduKush    4.Rocky Mountains", geographyEasy, 2),
    Question("Which of the following is the capital of Bangladesh?", "1.Azamgarh    2.Lucknow    3.Chittagong    4.Dhaka", geographyEasy, 4),
    Question("Which desert covers a significant portion of southeastern Pakistan?", "1.Thar    2.Thal    3.Kharan    4.Sahara", geographyEasy, 1),
    Question("Which of the following is the capital of Canada?", "1.Montreal    2.Edmunton    3.Ottowa    4.Toronto", geographyEasy, 3)
    };

    Question mgeographyQuestion[5] = {
    Question("which of the following is the capital of Hungary?", "1.Vienna    2.Budapest    3.Prague    4.Zurich", geographyMedium, 2),
    Question("Panama Canal links Pacific and which ocean?", "1.Antarctic    2.Arctic    3.Indian    4.Atlantic", geographyMedium, 4),
    Question("Which of the following countries is totally landlocked by South-Africa", "1.Uganda    2.Mozambique    3.Lesotho    4.Kenya", geographyMedium, 3),
    Question("which of the following is the capital of austria?", "1.Prague    2.Vienna    3.Budapest    4.Zurich", geographyMedium, 2),
    Question("which of the following is the capital of Mexico?", "1.Oaxaca    2.Albaqerque    3.Mexico City    4.Tijuana", geographyMedium, 3)
    };

    Question hgeographyQuestion[5] = {
    Question("Which of the following is the capital of Vietnam?", "1.Phnom Penh    2.Kuala Lampur    3.Hanoi    4.Manila", geographyHard, 3),
    Question("Which of the following is the capital of Romania?", "1.Tallinn    2.Kiev    3.Bucharest    4.Minsk", geographyHard, 3),
    Question("Which of the following is the biggest lake in the World?", "1.Michigan    2.Nile    3.Indus    4.Caspian Sea", geographyHard, 4),
    Question("Which of the following is the capital of Nigeria?", "1.Timbuktu    2.Abuja    3.Khutmundu    4.Thimphu", geographyHard, 2),
    Question("Which of the following is the capital of Estonia", " 1.Kiev    2.Tallinn    3.Minsk    4.Bucharest", geographyHard, 2)
    };



    Question eCSQuestion[5] = {
    Question("What does CPU mean?", "1.centre processor unit    2.central processing unit    3.central processor unit    4.central process unit", CSEasy, 2),
    Question("Which of the following is not an input device?", "1.Mouse    2.Keyboard    3.Monitor    4.Microphone", CSEasy, 3),
    Question("What is the term for a small piece of code that performs a specific task?", "1.loop    2.data type    3.condition    4.Function", CSEasy, 4),
    Question("What is the basic unit of storage in a computer's memory?", "1.bit    2.byte    3.megabyte    4.kilobyte", CSEasy, 2),
    Question("Which of the following is not an output device?", "1.Mouse    2.Speaker    3.Printer    4.Monitor", CSEasy, 1)
    };

    Question mCSQuestion[5] = {
    Question("What does HTTP mean?", "1.hi-transmission text protocol    2.hypertext transfer protocol    3.hi-tech transfer protocol    4.hypertest transfer protocol", CSMedium, 2),
    Question("Which concept in cybersecurity involves verifying the identity of users or systems before granting access?", "1.Authentication    2.Authorization    3.Encryption    4.Firewalling", CSMedium, 1),
    Question("Which programming language is often used for developing mobile applications on the Android platform?", "1.Swift    2.Java    3.C#    4.C++", CSMedium, 2),
    Question("What does IP stand for?", "1.Internet protocol    2.intranet protocol    3.Interconnection protocol    4.Internal protocol", CSMedium, 1),
    Question("which language is known for creating AI models?", "1.Python    2.C#    3.Rust    4.C", CSMedium, 1)
    };

    Question hCSQuestion[5] = {
    Question("Which of the following language was developed by microsoft for Desktop-App DEV?", "1.Ruby    2.Rust    3.C++    4.C#", CSHard, 4),
    Question("Which algorithm is used for routing data packets in the Internet?", "1.Dijkstra's algorithm    2.A* algorithm    3.    Bellman-Ford algorithm    4.Floyd-Warshall algorithm", CSHard, 1),
    Question("GNU project was created by which Computer Scientist?", "1.Richard Stallman    2.Bjarne Stroustrap    3.Ken Thompson    4.Dennis Ritchie", CSHard, 1),
    Question("Which data structure is typically used to implement a priority queue?", "1.Vector    2.Hash map    3.Stack    4.Heap", CSHard, 4),
    Question("Which algorithm is commonly used for natural language processing tasks such as machine translation?", "1.QuickSort    2.Dijkstra's algorithm    3.A* algorithm    4.Recurrent Neural Networks (RNN)", CSHard, 4)
    };



    Question eScienceQuestion[5] = {
    Question("What is the process by which plants make their own food using sunlight?", "1.Photosynthesis    2.Respiration    3.Digestion    4.Transpiration", scienceEasy, 1),
    Question("Which of the following is the smallest planet in our solar system?", "1.Venus    2.Earth    3.Mercury    4.Mars", scienceEasy, 3),
    Question("Which of these animals is a mammal?", "1.crocodile    2.whale    3.frog    4.chicken", scienceEasy, 2),
    Question("Which of these materials is a good conductor of electricity?", "1.Wood    2.Rubber    3.Plastic    4.Metal", scienceEasy, 4),
    Question("What force pulls objects towards the center of the Earth?", "1.Electricity    2.Gravity    3.Magnetism    4.Friction", scienceEasy, 2)
    };

    Question mScienceQuestion[5] = {
    Question("What is the chemical symbol for the element gold?", "1.Au    2.Ag    3.Go    4.Gl", scienceMedium, 1),
    Question("What is the process by which light is bent as it passes through different materials?", "1.Reflection    2.Dispersion    3.Refraction    4.Diffraction", scienceMedium, 3),
    Question("What gas do plants use from the air to make their own food?", "1.Carbon dioxide    2.Oxygen    3.Nitrogen    4.Hydrogen", scienceMedium, 1),
    Question("What is the SI unit of measure for electric current?", "1.Ampere    2.Volt    3.Watt    4.Ohm", scienceMedium, 1),
    Question("In which process do plants release oxygen into the atmosphere?", "1.Photosynthesis    2.Respiration    3.Transpiration    4.Fermentation", scienceMedium, 1)
    };

    Question hScienceQuestion[5] = {
    Question("Which scientist is credited with formulating the theory of general relativity?", "1.Isaac Newton    2.Albert Einstein    3.Niels Bohr    4.Galileo Galilei", scienceHard, 2),
    Question("Which type of electromagnetic radiation has the shortest wavelength?", "1.Radio waves    2.Microwaves    3.X-rays    4.Gamma rays", scienceHard, 4),
    Question("What is the process of a cell engulfing large particles or other cells called?", "1.Osmosis    2.Diffusion    3.Phagocytosis    4.Active transport", scienceHard, 3),
    Question("Which component of blood is responsible for transporting oxygen to body tissues?", "1.Platelets    2.White blood cells    3.Plasma    4.Red blood cells", scienceHard, 4),
    Question("Which subatomic particle is exchanged between atoms during a chemical reaction?", "1.Neutron    2.Electron    3.Proton    4.Positron", scienceHard, 2)
    };



    int totalQuestions = 5;
    bool flag = false;
    welcome();
    system("CLS");
    cout<<"\nEnter your name: ";
    getline(cin,playerName);
    

    do
    {
        system("CLS");
        cout << "\n1.Undertake the Quiz\t\t2.Show Score\t\t3.Exit\n\n";

        switch(inputValidation("Enter your choice: ", mainMenuChoice))
        {

            case 1:
                system("CLS");
                cout<<"1.History\t2.Geography\t3.Computer Science\t4.Science\n\n";

                

                    switch(inputValidation("Enter your preferred category: ", categoryChoice))
                    {
                        case 1:
                            cout<<"1.easy\t2.medium\t3.hard\n\n";

                                switch(inputValidation("Enter your preferred difficulty: ", difficultyChoice))
                                {
                                    case 1:
                                        system("CLS");
                                        for (int i = 0; i < totalQuestions; i++)
                                        {
                                            cout << endl << i+1 << ": ";
                                            ehistoryQuestion[i].askQuestion();
                                            cout << "Enter your Option(1-4): ";
                                            cin >> questionChoice;
                                            if(questionChoice == ehistoryQuestion[i].getCorrectOption())
                                            {  HE.updateScore(); }    
                                        }
                                        HE.displayScore();
                                        HE.updateIndividualFile(playerName);
                                        HE.updateLeaderboard(playerName);
                                        HE.updateIndividualcsvFile(playerName);
                                        HE.updateIndividualBinaryFile(playerName);
                                        break;

                                    case 2:
                                        system("CLS");
                                        for (int i = 0; i < totalQuestions; i++)
                                        {
                                            cout << i+1 << ": ";
                                            mhistoryQuestion[i].askQuestion();
                                            cout << "Enter your Option(1-4): ";
                                            cin >> questionChoice;

                                            if(questionChoice == mhistoryQuestion[i].getCorrectOption())
                                            {  HM.updateScore(); }    
                                        }
                                        HM.displayScore();
                                        HM.updateIndividualFile(playerName);
                                        HM.updateLeaderboard(playerName);
                                        break;

                                    case 3:
                                        system("CLS");
                                        for (int i = 0; i < totalQuestions; i++)
                                        {
                                            cout << i+1 << ": ";
                                            hhistoryQuestion[i].askQuestion();
                                            cout << "Enter your Option(1-4): ";
                                            cin >> questionChoice;

                                            if(questionChoice == hhistoryQuestion[i].getCorrectOption())
                                            {  HH.updateScore(); }    
                                        }
                                        HH.displayScore();
                                        HH.updateIndividualFile(playerName);
                                        HH.updateLeaderboard(playerName);
                                        break;
                                        
                                    default:
                                        cout<<"enter a valid option...\n";
                                        break;
                                }
                            break;

                        case 2:
                            cout<<"1.easy\t2.medium\t3.hard\n\n";
                            
                                switch(inputValidation("Enter your preferred difficulty: ", difficultyChoice))
                                {
                                    case 1:
                                        for (int i = 0; i < totalQuestions; i++)
                                        {
                                            cout << i+1 << ": ";
                                            egeographyQuestion[i].askQuestion();
                                            cout << "Enter your Option(1-4): ";
                                            cin >> questionChoice;

                                            if(questionChoice == egeographyQuestion[i].getCorrectOption())
                                            {  GE.updateScore(); }    
                                        }
                                        GE.displayScore();
                                        GE.updateIndividualFile(playerName);
                                        GE.updateLeaderboard(playerName);
                                        break;
                                    
                                    case 2:
                                        for (int i = 0; i < totalQuestions; i++)
                                        {
                                            cout << i+1 << ": ";
                                            mgeographyQuestion[i].askQuestion();
                                            cout << "Enter your Option(1-4): ";
                                            cin >> questionChoice;

                                            if(questionChoice == mgeographyQuestion[i].getCorrectOption())
                                            {  GM.updateScore(); }    
                                        }
                                        GM.displayScore();
                                        GM.updateIndividualFile(playerName);
                                        GM.updateLeaderboard(playerName);
                                        break;
                                    
                                    case 3:
                                        for (int i = 0; i < totalQuestions; i++)
                                        {
                                            cout << i+1 << ": ";
                                            hgeographyQuestion[i].askQuestion();
                                            cout << "Enter your Option(1-4): ";
                                            cin >> questionChoice;

                                            if(questionChoice == hgeographyQuestion[i].getCorrectOption())
                                            {  GH.updateScore(); }    
                                        }
                                        GH.displayScore();
                                        GH.updateIndividualFile(playerName);
                                        GH.updateLeaderboard(playerName);
                                        break;
                                    
                                    default:
                                        cout<<"enter a valid option...\n";
                                        break;
                                }
                            break;

                        case 3:
                            cout<<"1.easy\t2.medium\t3.hard\n\n";

                                switch(inputValidation("Enter your preferred difficulty: ", difficultyChoice))
                                {
                                    case 1:
                                        for (int i = 0; i < totalQuestions; i++)
                                        {
                                            cout << i+1 << ": ";
                                            eCSQuestion[i].askQuestion();
                                            cout << "Enter your Option(1-4): ";
                                            cin >> questionChoice;

                                            if(questionChoice == eCSQuestion[i].getCorrectOption())
                                            {  CE.updateScore(); }    
                                        }
                                        CE.displayScore();
                                        CE.updateIndividualFile(playerName);
                                        CE.updateLeaderboard(playerName);
                                        break;
                                    
                                    case 2:
                                        for (int i = 0; i < totalQuestions; i++)
                                        {
                                            cout << i+1 << ": ";
                                            mCSQuestion[i].askQuestion();
                                            cout << "Enter your Option(1-4): ";
                                            cin >> questionChoice;

                                            if(questionChoice == mCSQuestion[i].getCorrectOption())
                                            {  CM.updateScore(); }    
                                        }
                                        CM.displayScore();
                                        CM.updateIndividualFile(playerName);
                                        CM.updateLeaderboard(playerName);
                                        break;
                                    
                                    case 3:
                                        for (int i = 0; i < totalQuestions; i++)
                                        {
                                            cout << i+1 << ": ";
                                            hCSQuestion[i].askQuestion();
                                            cout << "Enter your Option(1-4): ";
                                            cin >> questionChoice;

                                            if(questionChoice == hCSQuestion[i].getCorrectOption())
                                            {  CH.updateScore(); }    
                                        }
                                        CH.displayScore();
                                        CH.updateIndividualFile(playerName);
                                        CH.updateLeaderboard(playerName);
                                        break;
                                    
                                    default:
                                        cout<<"enter a valid option...\n";
                                        break;
                                }
                            break;

                        case 4:
                            cout<<"1.easy\t2.medium\t3.hard\n\n";

                                switch(inputValidation("Enter your preferred difficulty: ", difficultyChoice))
                                {
                                    case 1:
                                        for (int i = 0; i < totalQuestions; i++)
                                        {
                                            cout << i+1 << ": ";
                                            eScienceQuestion[i].askQuestion();
                                            cout << "Enter your Option(1-4): ";
                                            cin >> questionChoice;

                                            if(questionChoice == eScienceQuestion[i].getCorrectOption())
                                            {  SE.updateScore(); }    
                                        }
                                        SE.displayScore();
                                        SE.updateIndividualFile(playerName);
                                        SE.updateLeaderboard(playerName);
                                        break;
                                    
                                    case 2:
                                        for (int i = 0; i < totalQuestions; i++)
                                        {
                                            cout << i+1 << ": ";
                                            mScienceQuestion[i].askQuestion();
                                            cout << "Enter your Option(1-4): ";
                                            cin >> questionChoice;

                                            if(questionChoice == mScienceQuestion[i].getCorrectOption())
                                            {  SM.updateScore(); }    
                                        }
                                        SM.displayScore();
                                        SM.updateIndividualFile(playerName);
                                        SM.updateLeaderboard(playerName);
                                        break;
                                    
                                    case 3:
                                        for (int i = 0; i < totalQuestions; i++)
                                        {
                                            cout << i+1 << ": ";
                                            hScienceQuestion[i].askQuestion();
                                            cout << "Enter your Option(1-4): ";
                                            cin >> questionChoice;

                                            if(questionChoice == hScienceQuestion[i].getCorrectOption())
                                            {  SH.updateScore(); }    
                                        }
                                        SH.displayScore();
                                        SH.updateIndividualFile(playerName);
                                        SH.updateLeaderboard(playerName);
                                        break;
                                    
                                    default:
                                        cout<<"enter a valid option...\n";
                                        break;

                                }
                            break;

                        default:
                            cout<<"enter a valid option...\n";
                            break;
                    }
                break;

            case 2:
                system("CLS");
                cout<<"1.individual score\t\t2.leaderboard\t\t3.back to main menu\n\n";
                
                    switch(inputValidation("Enter your preferred Option: ", scoreChoice))
                    {
                        case 1:
                            system("CLS");
                            cout<<"1.Text\t\t2.CSV\t\t3.Binary\n\n";

                                switch(inputValidation("Enter your preferred Format: ", scoreChoice))
                                {
                                    case 1:
                                        system("CLS");
                                        showIndividualScore();
                                        break;
                                    
                                    case 2:
                                        system("CLS");
                                        showIndividualCsv();
                                        break;

                                    case 3:
                                        system("CLS");
                                        showIndividualBinary();   
                                        break;

                                    default:
                                        cout<<"enter a valid option...\n";
                                        break;
                                }
                            
                            break;

                        case 2:
                            system("CLS");
                            showLeaderboard();
                            break;

                        case 3:
                            break;

                        default:
                            cout<<"enter a valid option...\n";
                            break;
                    }
                break;
            
            case 3:
                flag = true;
                break;

            default:
                cout<<"enter a valid option...\n";
                break;
        }
    }while(!flag);   
    return 0;
}