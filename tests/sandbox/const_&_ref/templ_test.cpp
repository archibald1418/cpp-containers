struct i{
	typedef int value;
};

struct j : public i{};

int main(){
	j::value c = 5;
};
