
class ogltext {

    public:
    enum NUM {
        ZERO = 0,
        ONE,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE
    };
    static std::vector<float> zero;
    static std::vector<float> one;
    static std::vector<float> generateMap(NUM choice);
};