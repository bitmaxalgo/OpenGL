const int WINDOW_WIDTH_M = 800;
const int WINDOW_HEIGHT_M = 600;

class Paddle {

    public:

    constexpr static float paddle_speed = 0.01f;

    constexpr static float paddle_width_ndc = 0.03f;
    constexpr static float paddle_width_halved_ndc = (paddle_width_ndc / 2.0f);

    constexpr static float paddle_height_ndc = 0.3f;
    constexpr static float paddle_height_halved_ndc = (paddle_height_ndc / 2.0f);

    constexpr static float paddle_upper_boundary{1.0f - (paddle_height_ndc)};
    constexpr static float paddle_lower_boundary{-1.0f + (paddle_height_ndc)};


    float x_offset,y_offset;
    Paddle(float x_offset, float y_offset) : x_offset{x_offset}, y_offset{y_offset} {}
};

class Ball {
    public:
    Ball(float x = 0.0f, float speedx = 0.01f, float y = 0.0f, float speedy = 0.01f) : x{x},speedx{speedx}, y{y},speedy{speedy} {}
    float x,y,speedx,speedy;
    

    static const GLuint vertex_number{30};
    static constexpr float ball_radius{0.03f};
    static const GLuint draw_number{vertex_number + 2};
    static constexpr float bounce_boundary{1.0f-ball_radius};

    void moveball();
};

void Ball::moveball() {
    float ball_boundary = Ball::bounce_boundary;

    if (this->x > ball_boundary) {
        this->x = 0.0f;
        this->speedx *= -1;
    }
    if (this->x < -ball_boundary) {
        this->x = 0.0f;
        this->speedx *= -1;
    }
    if (this->y > ball_boundary) {
        this->y = ball_boundary;
        this->speedy *= -1;
    }
    if (this->y < -ball_boundary) {
        this->y = -ball_boundary;
        this->speedy *= -1;
    }

    this->x += speedx;
    this->y += speedy;
}

void drawZero(GLuint zero_array_index, GLint &zero_boolean_location, std::vector<float> &zero_number, GLuint fragment_color_location);
std::vector<float> createPaddleVertices(); 
void drawBackdrop(GLint &backdrop_boolean_location, GLuint backdrop_array_index, GLuint fragment_color_location);
void drawBall(GLint &ball_boolean_location, GLuint ball_array_index, GLuint fragment_color_location);
void moveBall(GLint &ball_vec2_location, Ball &ball_object);
void drawPaddles(GLint &paddle_boolean_location, GLuint paddle_array_index, GLuint fragment_color_location, GLuint &paddle_vec2_location, Paddle &paddle_one, Paddle &paddle_two);
void movePaddles(GLFWwindow * window, Paddle &paddle_one, Paddle &paddle_two);      // PADDLE MOVE & WINDOW COLLISION DETECtION
void checkCollision(Paddle &paddle_one, Paddle &paddle_two, Ball &ball_object);