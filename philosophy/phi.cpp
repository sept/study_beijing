#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
using namespace std;

void * func(void *arg);

class Chopstick
{
public:
	Chopstick(int id);
	~Chopstick()
	{
	}

	pthread_mutex_t& get_mutex();
	int get_id() const;

private:
	pthread_mutex_t mylock;
	int m_id;
};

Chopstick::Chopstick(int id)
:m_id(id)
{
	pthread_mutex_init(&mylock, NULL);
}

pthread_mutex_t& Chopstick::get_mutex()
{
	return mylock;
}

int Chopstick::get_id() const
{
	return m_id;
}

class Philosophy
{
public:
	Philosophy(Chopstick* left, Chopstick* right, int id);
	~Philosophy()
	{
	};
	
	void think();
	void eat();
	void pickup();
	void putdown();
	void wait4end();

private:
	Chopstick *m_left;
	Chopstick *m_right;
	int m_id;
	pthread_t tid;
};

Philosophy::Philosophy(Chopstick* left, Chopstick* right, int id)
:m_id(id), m_left(left), m_right(right)
{
	srand(time(NULL));
	pthread_create(&tid, NULL, func, (void *)this);
	//pthread_create(&tid, NULL, func, NULL);
}

void Philosophy::think()
{
	int t = rand() % 10;
	cout << "philosophy" << m_id << "is thinking for " 
		<< t << " seconds" << endl;
	usleep(t);
}

void Philosophy::eat()
{
	int t = rand() % 10;
	cout << "philosophy" << m_id << "is eating for " 
		<< t << " seconds" << endl;
	usleep(t);
}

void Philosophy::pickup()
{
	if(m_id == 0)
	{
#if 0
		//第一个人按同样顺序拿筷子
		pthread_mutex_lock(&m_left->get_mutex());
		pthread_mutex_lock(&m_right->get_mutex());
#else
		//第一个人按不同顺序拿筷子
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

void Philosophy::putdown()
{
	pthread_mutex_unlock(&m_left->get_mutex());
	pthread_mutex_unlock(&m_right->get_mutex());
}

void * func(void *arg)
{
	Philosophy * THIS = (Philosophy *)arg;
	while(1)
	{
		THIS->think();
		THIS->pickup();
		THIS->eat();
		THIS->putdown();
	}

	return NULL;
}

void Philosophy::wait4end()
{
	pthread_join(tid, NULL);
}

int main()
{
	//创建5支筷子对象
	Chopstick a(0), b(1), c(2), d(3), e(4);

	//创建5个哲学家对象
	Philosophy A(&a, &b, 0), B(&b, &c, 1), C(&c, &d, 2);
	Philosophy D(&d, &e, 3), E(&e, &a, 4);

	//调用各自的pthread_join()
	A.wait4end();
	B.wait4end();
	C.wait4end();
	D.wait4end();
	E.wait4end();

	return 0;
}
