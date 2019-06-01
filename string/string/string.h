#include <assert.h>

class String
{
public:
	typedef char* iterator;
	typedef const char* const_iterator;

	const_iterator begin() const
	{
		return _str;
	}

	const_iterator end() const
	{
		return _str + _size;
	}

	iterator begin()
	{
		return _str;
	}

	iterator end()
	{
		return _str + _size;
	}

	String(const char* str = "")
		:_str(nullptr)
		, _capacity(0)
	{
		_size = strlen(str);
		Reserve(_size);
		strcpy(_str, str);
	}

	// s2(s1)
	String(const String& s)
		:_str(nullptr)
		, _size(0)
		, _capacity(0)
	{
		String tmp(s._str);
		Swap(tmp); // tmp.Swap(*this);
	}

	// s1 = s3
	String& operator=(String s)
	{
		Swap(s);
		return *this;
	}

	// s1.Swap(s2)
	void Swap(String& s)
	{
		std::swap(_str, s._str);
		std::swap(_size, s._size);
		std::swap(_capacity, s._capacity);

	}

	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}
	}

	void PushBack(char ch)
	{
		/*if (_size == _capacity)
		{
		Reserve(_capacity * 2);
		}

		_str[_size] = ch;
		++_size;
		_str[_size] = '\0';*/

		Insert(_size, ch);
	}

	void Append(const char* str)
	{
		/*	size_t len = strlen(str);
			if (_size + len > _capacity)
			{
			Reserve(_size + len);
			}

			strcpy(_str + _size, str);
			_size += len;*/

		Insert(_size, str);
	}

	// s1 += 'c'
	String& operator+=(char ch)
	{
		PushBack(ch);
		return *this;
	}

	String& operator+=(const char* str)
	{
		Append(str);
		return *this;
	}

	void Insert(size_t pos, char ch)
	{
		assert(pos <= _size);

		if (_size == _capacity)
		{
			Reserve(_capacity * 2);
		}

		for (size_t i = _size; i >= pos; --i)
		{
			_str[i + 1] = _str[i];
		}
		_str[pos] = ch;
		_size++;
	}

	void Insert(size_t pos, const char* str);
	void Erase(size_t pos = 0, size_t len = npos);
	size_t Find(char ch, size_t pos = 0);
	size_t Find(const char* str, size_t pos = 0);
	bool operator<(const String& s)const;
	bool operator<=(const String& s)const;
	bool operator>(const String& s)const;
	bool operator>=(const String& s)const;
	bool operator==(const String& s)const;
	bool operator!=(const String& s)const;


	// s1 + 'c'
	String operator+(char ch) const
	{
		String tmp(*this);
		tmp.PushBack(ch);
		return tmp;
	}

	String& operator+(const char* str)
	{
		String tmp(*this);
		tmp.Append(str);
		return tmp;
	}

	char* c_str() const
	{
		return _str;
	}

	char& operator[](size_t pos)
	{
		assert(pos < _size);

		return _str[pos];
	}

	const char& operator[](size_t pos) const
	{
		assert(pos < _size);

		return _str[pos];
	}

	size_t Size() const
	{
		return _size;
	}

	size_t Capacity() const
	{
		return _capacity;
	}

	void Reserve(size_t n)
	{
		if (n == 0 || n > _capacity)
		{
			//size_nt ewsize = (n + 7) & ( ~7);
			size_t newsize = n;
			if (n % 8 != 0)
				newsize = (n / 8 + 1) * 8;
			else
				newsize = n + 8;

			char* newstr = new char[newsize];
			if (_str)
				strcpy(newstr, _str);
			_str = newstr;
			_capacity = newsize - 1;
		}
	}

	void Resize(size_t n, char ch = '\0')
	{
		if (n <= _size)
		{
			_size = n;
			_str[_size] = '\0';
		}
		else
		{
			Reserve(n);

			for (size_t i = _size; i < n; ++i)
			{
				_str[i] = ch;
				++_size;
			}
			_str[_size] = '\0';
		}
	}

private:
	char*  _str;
	size_t _size;
	size_t _capacity;

	static size_t npos;
};

size_t String::npos = -1;

