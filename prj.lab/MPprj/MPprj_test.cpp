#include<MPprj/MPprj.h>
#include<algorithm>
#include <random>
using namespace matplot;

//��� ����� n : �� 1 �� 200000 ������������ � �����? n{2,10,100,500,2500, 5000, 7500, 12500, 25000, 50000, 100000, 200000}
//m �� 1 �� n
//M ������� ��� n. � ��������������� ������� pop_back() � push �������� �� n. = �������� ����� �����. ������ ������ n ������� �� ������. 
//������ ������� t/n (n) ��� ������ �����������? 


const std::vector<int> N{ 2, 10, 100, 500, 2500, 5000, 7500, 12500, 25000, 50000, 100000, 200000 }; //������ �������� n

int main() {
	std::vector<int>(*inp_first_ex)(int, std::vector<int>) = input_first_example;//��������� �� ����������� �������
	std::vector<int>(*inp_sec_ex)(int, std::vector<int>) = input_second_example;
	void(*outp_first_ex)(int, std::vector<int>) = output_first_example;
	void(*outp_sec_ex)(int, std::vector<int>) = output_second_example;


	//���� ��� m/M ��� 1/2
	// m = 1, M = n
	// m = n/2, M = n
	// m = n, M = n
	
	//������� ��� ������� � ����� m/M
	std::vector<float> m_M_input_duration1, m_M_input_duration2, m_M_output_duration1, m_M_output_duration2;

	for (int n : N) { //������
		int m = n/2, M = n;
		for (size_t i = 0; i < 2; i++)
		{
			std::vector<int> test(m);//��������� �������� ������
			std::iota(test.begin(), test.end(), 1);
			test.pop_back();
			test.push_back(M);//������������ ������ ������������ �����
			
			if (!i) //�������� ������ test �� ������������ ���������� ���������
				for (size_t j = 0; j < m; j++) test.push_back(test[j]);
			auto rng = std::default_random_engine{};
			std::shuffle(test.begin(), test.end(), rng); //������������ ������

			std::pair<std::chrono::duration<float>, std::chrono::duration<float>> duration1 = //�������� ���� �������� �������
				Timer_for_solution(inp_first_ex, outp_first_ex, n, test); 
			m_M_input_duration1.push_back(duration1.first.count());
			m_M_output_duration1.push_back(duration1.second.count());

			std::pair<std::chrono::duration<float>, std::chrono::duration<float>> duration2 = //������ ��� ������� �������
				Timer_for_solution(inp_sec_ex, outp_sec_ex, n, test);
			m_M_input_duration2.push_back(duration2.first.count());
			m_M_output_duration2.push_back(duration2.second.count());

			m += (n / 2); //��� ��� ��������� m/M ����� 1/2 
		}

	}

	for (size_t i = 0; i < m_M_input_duration1.size(); i++)
	{
		std::cout << m_M_input_duration1[i] << std::endl;
	}
}