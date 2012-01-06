#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

void* func(void* arg);

class Chopstick
{
public:
	Chopstick(int id)
	:id(id) //this->id(id) is error! 
	{
		pthread_mutex_init(&chp, NULL);
	};

	~Chopstick(){};

	int get_chop_id() const { return id; };

	//if add "const" will get const pthread_mutex_t&, error!
	//pthread_mutex_t& get_mutex() const
	pthread_mutex_t& get_mutex()
	{
		return chp;
	}

private:
	pthread_mutex_t chp;
	int id;
};

class Philosophy
{
public:
	Philosophy(Chopstick *left, Chopstick *right, int id)
	:m_id(id)
	{
		srand(time(NULL));
		m_left = left;
		m_right = right;
		pthread_create(&tid, NULL, func, (void *)this);
	}

	~Philosophy(){};

	void do_all()
	{
		while(1)
		{
			think();
			pickup();
			eat();
			putdown();
		}
	}

	void eat()
	{
		int t = rand() % 10;
		cout << "philosophy" << m_id << "is eating for "
			<< t << " second" << endl;
		usleep(t);
	}

	void pickup()
	{
		if(m_id == 0)
		{
#if 1
			pthread_mutex_lock(&m_left->get_mutex());
			pthread_mutex_lock(&m_right->get_mutex());
#else
			pthread_mutex_lock(&m_right->get_mutex());
			pthread_mutex_lock(&m_left->get_mutex());
#endif
		}
		else
		{
			pthread_mutex_lock(&m_left->get_mutex());
			pthread_mutex_lock(&m_right->get_mutex());
		}
	}

	void putdown()
	{
		pthread_mutex_unlock(&m_left->get_mutex());
		pthread_mutex_unlock(&m_right->get_mutex());
	}

	void think()
	{
		int t = rand() % 10;
		cout << "philosophy" << m_id << "is thinking for "
			<< t << " second" << endl;
		usleep(t);
	}

	void wait4finished()
	{
		pthread_join(tid, NULL);
	}

private:
	Chopstick *m_left;
	Chopstick *m_right;
	pthread_t tid;
	int m_id;
};

void* func(void* arg) //线程函数，在里面调用类的成员函数
{
	Philosophy * THIS = (Philosophy *)arg;
	THIS->do_all();

	return NULL;
}

int main()
{
	Chopstick a(0), b(1), c(2), d(3), e(4); //5支筷子用相应编号初始化

	//五个哲学家
	Philosophy A(&a, &b, 0), B(&b, &c, 1), C(&c, &d, 2);  
	Philosophy D(&d, &e, 3), E(&e, &a, 4);

	//调用每个线程的pthread_join()
	A.wait4finished();
	B.wait4finished();
	C.wait4finished();
	D.wait4finished();
	E.wait4finished();

	return 0;
}
