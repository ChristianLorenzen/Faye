function testfunc() 
{
    var thisIsALoser = "Loser";

    string stringTest = "String COntent";

    int intTest = 5;
    int twoTest = 2;

    #int final = intTest + twoTest;

    print(thisIsALoser);
    print(stringTest);
    print(intTest);
    #int invalidInt = "Hello There";

    float floatTest = 37;

    bool isTrue = true;

    bool isFalse = false;

    #boolStuff bool = true;

    print(thisIsALoser, intTest, floatTest, isTrue, isFalse);

    function into(string testingT) {
        #ignore comment
        print("Before print test");
        #print(testingT);
    };

    into("Hello");
};


function testRun() {
    print("Hi");
    testfunc();
    #testfunc();
    #This can be ignored
    into();
    #Ignore as well
    print("Comments aren't giving issue");
};



string test = "Hello";

print(test); #This is a line comment which should be ignored

testRun("hello");

function test(string x) {
    print(x);
};

/*

test(15);
test(15);
test(true);
test("TestString");
