#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm> 
using namespace std;
ifstream fin("input.txt");
ofstream fout("output.csv");

struct stu{
	string name;
	int id;
	double score;
	int ScoreRank;
};

bool inputstu(int *n,int* full,stu student[]){
	if (!fin.is_open() || !fout.is_open()) {
		cerr << "无法打开文件\n";
		return 0; 
	}
        
    cout<<"请输入需要统计的学生数量："; 
    cin>>*n;
    cout<<"请输入该科目的满分：", 
	cin>>*full;
	for(int i=0;i<*n;i++){
		fin>>student[i].name>>student[i].id>>student[i].score; 
		if(student[i].score>*full || student[i].score<0){
			cerr<<"\n学生成绩范围错误，自动退出中。";
			return 0;
		}
	}		
	if((*n)==0||(*full)==0||(*n)>30){
		cerr<<"\n数据读取失败，自动退出中。";
		return 0;
	}
	return 1;
}

bool cmp(stu x,stu y){
	if(x.score>y.score)
		return 1;
	return 0;
}

void Rank(stu student[],int n){
	sort(student,student+n,cmp);
	int temp=1;
	for(int i=0;i<n;i++){
		if(i>0 && student[i].score==student[i-1].score)
			student[i].ScoreRank=i-(temp++)+1;
		else{
			student[i].ScoreRank=i+1;
			temp=1;
		}	
	}
} 

void statistics(stu student[],int n,int *score30,int *score60,int *score80,int *score100,int full){
	*score30=0;
	*score60=0;
	*score80=0;
	*score100=0; 
	for(int i=0;i<n;i++){
		if(student[i].score<0.3*full)
			(*score30)++;
		else if(student[i].score<0.6*full)
			(*score60)++;
		else if(student[i].score<0.8*full)
			(*score80)++;
		else
			(*score100)++;
	}
}
void analysis(stu student[],int *ScoreMax,int *ScoreMin,double *ScoreAve,int n,double full){
	double sum=0.0;
	for(int i=0;i<n;i++){
		if(student[i].score>student[*ScoreMax].score) 
			*ScoreMax=i;
		if(student[i].score<student[*ScoreMin].score) 
			*ScoreMin=i;
		sum+=student[i].score;
	}
	*ScoreAve=sum/n;
}

void stuoutput(stu student[], int n){
	Rank(student,n);
	fout<<"排名,学号,姓名,成绩\n";
	for(int i=0;i<n;i++){
		fout<<student[i].ScoreRank<<","<<student[i].id<<","<<student[i].name<<","<<student[i].score<<endl; 
	} 
} 


int main(){
	cout<<"正在进入系统，请确保输入正确的数值。\n按照参考样例，共30名学生，试卷满分100分。\n\n";
	int n=0,full=0,score30=0,score60=0,score80=0,score100=0,ScoreMax=0,ScoreMin=0;
	double ScoreAve=0;
	stu student[30];
	cout<<"\n上传数据中，请确保学生信息按指定格式存储在 input.csv。\n"; 
	if(inputstu(&n,&full,student))
		cout<<"\n数据读取已完成,正在分析中。\n";
	else{
		system("pause");
		return 0;
	}
		
	while(1) {
		int operation=0;
		cout<<"\n\n数据分析已完成，可执行下列操作；\n请选择需要执行的操作\n";
		cout<<"1. 成绩排序\n";
		cout<<"2. 成绩统计\n"; 
		cout<<"3. 成绩分析\n"; 
		cout<<"4. 导出数据并退出\n\n";
		cin>>operation;
	 
		switch(operation){
			case 1:
				Rank(student,n); 
				for(int i=0;i<n;i++)
					cout<<student[i].ScoreRank<<" "<<student[i].id<<"号 "<<student[i].name<<" "<<student[i].score<<" 分\n";
				cout<<"成绩排序已完成\n";
				break; 
			case 2:
				cout<<"按原始分百分比转换至100分后\n";
				statistics(student,n,&score30,&score60,&score80,&score100,full);
				cout<<"0-30分:"<<score30<<"人；\n";
				cout<<"30-60分:"<<score60<<"人；\n";
				cout<<"60-80分:"<<score80<<"人；\n";
				cout<<"80-100分:"<<score100<<"人；\n";
				cout<<"已完成\n";
				break;
			case 3:
				analysis(student,&ScoreMax,&ScoreMin,&ScoreAve,n,full);
				cout<<"平均分为： "<<ScoreAve<<endl;
				cout<<"最高分为："<<student[ScoreMax].id<<"号 "<<student[ScoreMax].name<<" "<<student[ScoreMax].score<<"分。\n";
				cout<<"最低分为："<<student[ScoreMin].id<<"号 "<<student[ScoreMin].name<<" "<<student[ScoreMin].score<<"分。\n";
				cout<<"成绩分析完成\n";
				
				
				break;
			case 4:
				stuoutput(student,n);
				cout<<"数据已导出，正在退出\n";
				system("pause");
				return 0; 
				break;
			default:
				cerr<<"输入错误，请重新输入\n";
				break;
		}
	}
	system("pause");
	return 0;
}

