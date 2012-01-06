#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
using namespace std;

void *func(void *arg);

class Chopstick{
public:
	Chopstick(int theId);
	~Chopstick();
	pthread_mutex_t& get_chp();

private:
	int id;
	pthread_mutex_t chp;
};

class Philosophy{
public:
	Philosophy(int theId, Chopstick& l, Chopstick& r);
	~Philosophy();
	void thinking();
	void eating();
	void pickup();
	void putdown();
	void wait4finished();

private:
	int id;
	Chopstick& left;
	Chopstick& right;
	pthread_t tid;
};


Philosophy::Philosophy(int theId, Chopstick& l, Chopstick& r)
:id(theId), left(l), right(r)
{
	cout << id << "号哲学家来了!" << endl;
	srand(time(NULL));
	pthread_create(&tid, NULL, func, (void*)this);
	//pthread_join(tid, NULL);//error!
}

Philosophy::~Philosophy()
{
	cout << id << "号哲学家离开了!" << endl;
}

void Philosophy::thinking()
{
	int seconds = rand()%5;
	cout << id << "号哲学家思考了" << seconds << "秒" << endl;
	usleep(seconds);
}

void Philosophy::eating()
{
	int seconds = rand()%5;
	cout << id << "号哲学家吃饭花了" << seconds << "秒" << endl;
	usleep(seconds);
}

void Philosophy::pickup()
{
	if(id == 0)
	{
		pthread_mutex_lock(&(right.get_chp()));
		pthread_mutex_lock(&left.get_chp());
	}
	else
	{
		pthread_mutex_lock(&(left.get_chp()));
		pthread_mutex_lock(&(right.get_chp()));
	}
}

void Philosophy::putdown()
{
	pthread_mutex_unlock(&(left.get_chp()));
	pthread_mutex_unlock(&(right.get_chp()));
}

void Philosophy::wait4finished()
{
	pthread_join(tid, NULL);
}

void *func(void *arg)
{
	Philosophy *py = (Philosophy *)arg;
	while(1)
	{
		py->thinking();
		py->pickup();
		py->eating();
		py->putdown();
	}

	return NULL;
}

Chopstick::Chopstick(int theId)
:id(theId)
{
	pthread_mutex_init(&chp, NULL);
}

pthread_mutex_t& Chopstick::get_chp()
{
	return chp;
}

Chopstick::~Chopstick()
{

}

int main()
{
	//Chopstick a(0), b(1), c(2), d(3), e(4);//创建5支筷子对象
	Chopstick *a = new Chopstick(0);
	Chopstick *b = new Chopstick(1);
	Chopstick *c = new Chopstick(2);
	Chopstick *d = new Chopstick(3);
	Chopstick *e = new Chopstick(4);
	//Philosophy A(0, a, b), B(1, b, c), C(2, c, d), D(3, d, e), E(4, e, a);
	Philosophy A(0, *a, *b), B(1, *b, *c), C(2, *c, *d), D(3, *d, *e), E(4, *e, *a);
	A.wait4finished();
	B.wait4finished();
	C.wait4finished();
	D.wait4finished();
	E.wait4finished();
	delete a;
	delete b;
	delete c;
	delete d;
	delete e;
	return 0;
}
