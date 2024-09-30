import std;

int main() {
    my_std::string s = "Hello, world!";
    my_std::print(s);

    // Example of reading input
    my_std::print("Please enter something:");
    my_std::string input = my_std::read();
    my_std::print("You entered: " + input);

    return 0;
}
