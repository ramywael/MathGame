#include<iostream>
using namespace std;


enum enQuestionLevel {
	Easy=1,
	Medium=2,
	Hard=3,
	MixLevel=4,
};
enum enOperationType {
	Add=1,
	Sub=2,
	Mul=3,
	Div=4,
	Mix=5,
};

struct stQuetion {
	short number1;
	short number2;
	enQuestionLevel questionLevel;
	enOperationType operType;
	short correctAnswer;
	short userAnswer;
	bool isCorrect;
};
struct stQuiz {
	stQuetion questionList[100];
	short numberOfQuestions;
	enQuestionLevel questionLevel;
	enOperationType operationType;
	short numberOfCorrectAnswers=0;
	short numberOfWrongAnswers=0;
	bool isPassed = true;
};

short HowManyQuestions() {
	short numberOfQuestions=0;
	do {
		cout << "How Many Questions Do You Want ? ";
		cin >> numberOfQuestions;
	} while (numberOfQuestions < 1 || numberOfQuestions > 10 );
	return numberOfQuestions;
}
enQuestionLevel ReadQuestionLevel() {
	short questionLevel=0;
	do {
		cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";	
		cin >> questionLevel;
	} while (questionLevel < 1 || questionLevel > 4);
	return (enQuestionLevel)questionLevel;
}
enOperationType ReadOperationType() {
	short operationLevel=0;
	do {
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul,[4] Div, [5] Mix ? ";
		cin >> operationLevel;
	} while (operationLevel < 1 || operationLevel > 5);
	return (enOperationType)operationLevel;
}
short GenerateRandomNumber(short from, short to) {
	short randNumber = rand() % (to - from + 1) + from;
	return randNumber;
}

enOperationType GenerateRandomOperation(short from,short to) {
	short randOperationType = rand() % (to - from + 1) + from;
	return (enOperationType)randOperationType;
}

short SimpleCalculation(enOperationType operationTypo,short number1,short number2) {
	switch (operationTypo)
	{
	case Add:
		return number1 + number2;
		break;
	case Sub:
		return number1 - number2;
		break;
	case Mul:
		return number1 * number2;
		break;
	case Div:
		return number1 / number2;
		break;
	default:
		return number1 + number2;
		break;
	}
}

stQuetion GenerateQuestion(enQuestionLevel questionLevel,enOperationType opType) {
	stQuetion question;

	if (questionLevel == enQuestionLevel::MixLevel) {
		questionLevel = (enQuestionLevel)GenerateRandomNumber(1,3);
	}

	if (opType == enOperationType::Mix) {
		opType = (enOperationType)GenerateRandomOperation(1, 4);
	}
	question.operType = opType;
	switch (questionLevel)
	{
	case enQuestionLevel::Easy:
		question.number1 = GenerateRandomNumber(1,10);
		question.number2 = GenerateRandomNumber(1,10);
		question.correctAnswer = SimpleCalculation(opType,question.number1,question.number2);
		question.questionLevel = questionLevel;
		return question;
		break;
	case enQuestionLevel::Medium:
		question.number1 = GenerateRandomNumber(1, 20);
		question.number2 = GenerateRandomNumber(1, 20);
		question.correctAnswer = SimpleCalculation(opType, question.number1, question.number2);
		question.questionLevel = questionLevel;
		return question;
		break;
	case enQuestionLevel::Hard:
		question.number1 = GenerateRandomNumber(50, 100);
		question.number2 = GenerateRandomNumber(50, 100);
		question.correctAnswer = SimpleCalculation(opType, question.number1, question.number2);
		question.questionLevel = questionLevel;
		return question;
		break;
	default:
		break;
	}
	return question;

 }
 void GenerateQuizQuestions(stQuiz &quiz) {
	 for (short question = 0;question < quiz.numberOfQuestions;question++) {
		 quiz.questionList[question] = GenerateQuestion(quiz.questionLevel,quiz.operationType);
	 }
}
 short ReadUserAnswer() {
	 short userAnswer = 0;
	 cin >> userAnswer;
	 return userAnswer;
 }
 string getOperationSympol(enOperationType operationTypo) {
	 switch (operationTypo)
	 {
	 case enOperationType::Add:
		 return "+";
		 break;
	 case enOperationType::Sub:
		 return "-";
		 break;
	 case enOperationType::Mul:
		 return "*";
		 break;
	 case enOperationType::Div:
		 return "/";
		 break;
	 default:
		 break;
	 }
 }
 void PrintQuestion(stQuiz quiz,short questionIndex) {
	 cout << "Questions [" << questionIndex+1 << "/" << quiz.numberOfQuestions << "] \n\n";
	 cout << quiz.questionList[questionIndex].number1 << "\n";
	 cout << quiz.questionList[questionIndex].number2<< " " << getOperationSympol(quiz.questionList[questionIndex].operType);
	 cout << "\n\n---------------------------------\n\n";
 }
 void SetScreenColor(bool isCorrect=true) {
	 if (isCorrect) {
		 system("color 2F");
	 }
	 else {
		 system("color 4F");
		 cout << "\a";
	 }
 }
 void CorrectTheQuestionAnswer(stQuiz & quiz,short questionIndex) {
	 if (quiz.questionList[questionIndex].userAnswer != quiz.questionList[questionIndex].correctAnswer) {
		 quiz.numberOfWrongAnswers++;
		 quiz.questionList[questionIndex].isCorrect = false;
		 cout << "Wrong Answer :-( \n";
		 cout << "The Right Answr Is :" << quiz.questionList[questionIndex].correctAnswer << "\n\n";
	 }
	 else {
		 quiz.numberOfCorrectAnswers++;
		 quiz.questionList[questionIndex].isCorrect = true;
		 cout << "Right Answer :-) \n\n";
	 }
	 SetScreenColor(quiz.questionList[questionIndex].isCorrect);
 }

 bool AskAndCorrectQuestionListAnswers(stQuiz& quiz) {
	 for (short question = 0;question <quiz.numberOfQuestions;question++) {
		 PrintQuestion(quiz,question);
		 quiz.questionList[question].userAnswer = ReadUserAnswer();
		 CorrectTheQuestionAnswer(quiz,question);
	 }
	 return quiz.isPassed = (quiz.numberOfCorrectAnswers >= quiz.numberOfWrongAnswers);
 }
 string PrintPassOrFail(bool isPassed) {
	 if (isPassed) 
		 return "Passed :-)\n";
	 else
		 return "Fail :-( \n";
 }
 string getQuestionLevel(enQuestionLevel level) {
	 string arrQuestionLevel[4] = { "Easy","Medium","Hard","Mix" };
	 return arrQuestionLevel[level - 1];
 }
 string getOperationType(enOperationType type) {
	 string arrQuestionLevel[5] = { "+","-","*","/","Mix"};
	 return arrQuestionLevel[type - 1];
 }
 void  PrintQuizzResults(stQuiz quiz) {
	
		 cout << "---------------------------\n\n";
		 cout << "Final Result is :" << PrintPassOrFail(quiz.isPassed)<<"\n\n";
		 cout << "---------------------------\n\n";
		 cout << "Number Of Questions     :" << quiz.numberOfQuestions << "\n";
		 cout << "Question Level          :" << getQuestionLevel(quiz.questionLevel) << "\n";
		 cout << "Op Type                 :" << getOperationType(quiz.operationType) << "\n";
		 cout << "Number Of Correct Answers  :" << quiz.numberOfCorrectAnswers << "\n";
		 cout << "Number Of Wrong Answers    :" << quiz.numberOfWrongAnswers << "\n";
		 cout << "---------------------------\n\n";

	    SetScreenColor(quiz.isPassed);
}
void PlayGame() {
	stQuiz quiz;
	quiz.numberOfQuestions = HowManyQuestions();
	quiz.questionLevel = ReadQuestionLevel();
	quiz.operationType = ReadOperationType();
	GenerateQuizQuestions(quiz);
	AskAndCorrectQuestionListAnswers(quiz);
	PrintQuizzResults(quiz);	
}

void ResetScreen(){
	system("cls");
	system("color 0F");
}

void StartGame() {
	char playAgain = 'y';
	do {
		ResetScreen();
		PlayGame();
		cout << "Do You Want To Play Again Y/N ? ";
		cin >> playAgain;
	} while (playAgain == 'y' || playAgain == 'Y');
}
int main() {
	//Seeds the random number generator in C++, called only once
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}