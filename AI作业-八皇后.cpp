//回溯法求解N皇后问题
#include <vector>
#include <string>
#include <iostream>
using namespace std;


//放置皇后函数putQueen()
//在(x,y)处放置皇后并找到所有和它同行同列同对角线的位置
//然后更新attack数组，不能放皇后的地方置1，否则置0
void putQueen(int x, int y, vector<vector<int>> &attack) {
	//设置左、右、下、上、左下、左上、右下、右上8个方向
	int dx[] = { -1,1,0,0,-1,-1,1,1 };
	int dy[] = { 0,0,-1,1,-1,1,-1,1 };
	//在(x,y)处放置皇后
	attack[x][y] = 1;
	for (int i = 1; i < attack.size(); i++) {//从1到最大攻击距离
		for (int j = 0; j < 8; j++) {//遍历8个方向
			int nx = x + i * dx[j];
			int ny = y + i * dy[j];
			if (nx >= 0 && nx < attack.size() && ny >= 0 && ny < attack.size())//若遍历到的点在棋盘内
				attack[nx][ny] = 1;//将该点attack值置1
		}
	}
}


//递归函数backTrack()
//参数解释：
//k——当前处理行
//n——皇后个数
//queen——存储皇后的位置，即解的其中一行
//attack——标记皇后能攻击到的位置
//solve——存储N皇后的所有解
void backTrack(int k, int n, vector<string>&queen, vector<vector<int>>&attack, vector<vector<string>>&solve) {
	//递归结束条件
	//若当前处理到最后一行，说明找到一组解
	//并将结果queen存储至全集solve中
	if (k == n) {
		solve.push_back(queen);
		return;
	}
	//对当前行第k行循环试探皇后可能放置的位置
	for (int i = 0; i < n; i++) {
		if (attack[k][i] == 0)//若当前位置可以放置皇后
		{
			vector<vector<int>>tmp = attack;//保存回溯之前的attack数组
			queen[k][i] = 'Q';//更新当前位置的queen数组
			putQueen(k, i, attack);//更新当前位置的attack数组
			backTrack(k + 1, n, queen, attack, solve);//当前行已经放了皇后，开始对下一行进行递归试探
			attack = tmp;//恢复attack和queen之前的状态
			queen[k][i] = 'x';
		}
		//当前行当前列不能放皇后，i递增进行下一列的尝试
	}
}

//求解函数solveNQueens
//用二维向量保存结果
//每一行的摆放情况：x表示不摆放皇后，Q表示摆放皇后
//内层string类型的vector表示所有解中的一种情况
//如n=4，即解决四皇后问题时，内层第一个vector所有元素为	：
//xxQx
//Qxxx
//xxxQ
//xQxx
//外层vector则包含所有解，外层vector的size()即为解的个数
vector<vector<string>> solveNQueens(int n) {
	vector<vector<string>> solve;//所有解
	vector<vector<int>> attack;//皇后的攻击位置
	vector<string> queen;//皇后的位置
	//循环初始化attack和queen数组
	for (int i = 0; i < n; i++) {
		attack.push_back((vector<int>())); 
		for (int j = 0; j < n; j++) {
			attack[i].push_back(0);
		}
		queen.push_back(""); //先要添加一个空字符串才能使用string的append方法
		queen[i].append(n, 'x');
	}
	//开始递归求解
	backTrack(0, n, queen, attack, solve); 
	return solve;
}
//主函数测试，n=8解决八皇后问题
int main() {
	vector<vector<string>>result;
	result = solveNQueens(8);//解决8皇后问题，结果保存在result向量中

	cout << "8皇后问题共有" << result.size() << "种解法~~~";
	char ch;
	cout << "你是否想看所有解？(y/n)" << endl;
	cin >> ch;
	if (ch == 'y' || ch == 'Y') {//若选择是，输出所有解的棋盘
		for (int i=0;i<result.size();i++)
		{
			cout << "第" << i + 1 << "种解法：" << endl;
			for (int j=0;j<result[i].size();j++)
			{
				cout << result[i][j].c_str()<<endl;
			}
		}
	}
}