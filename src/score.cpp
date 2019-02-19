#include "score.h"
#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL

Score::Score(float x, float y, float z, color_t color)
{
    this->position = glm::vec3(x, y, z);

    static const GLfloat vertex_buffer_dataU[] = {
        0.5f, 0.5f, 0.0f,
        0.4f, 0.6f, 0.0f,
        0.4f, 0.4f, 0.0f,

        -0.5f, 0.5f, 0.0f,
        -0.4f, 0.6f, 0.0f,
        -0.4f, 0.4f, 0.0f,
        
        0.4f, 0.6f, 0.0f,
        0.4f, 0.4f, 0.0f,
        -0.4f, 0.4f, 0.0f,

        0.4f, 0.6f, 0.0f,
        -0.4f, 0.4f, 0.0f,
        -0.4f, 0.6f, 0.0f,
    };
    this->object[0] = create3DObject(GL_TRIANGLES, 12, vertex_buffer_dataU, color, GL_FILL);

    static const GLfloat vertex_buffer_dataL[] = {
        0.5f, -0.5f, 0.0f,
        0.4f, -0.6f, 0.0f,
        0.4f, -0.4f, 0.0f,

        -0.5f, -0.5f, 0.0f,
        -0.4f, -0.6f, 0.0f,
        -0.4f, -0.4f, 0.0f,

        0.4f, -0.6f, 0.0f,
        0.4f, -0.4f, 0.0f,
        -0.4f, -0.4f, 0.0f,

        0.4f, -0.6f, 0.0f,
        -0.4f, -0.4f, 0.0f,
        -0.4f, -0.6f, 0.0f,
    };
    this->object[3] = create3DObject(GL_TRIANGLES, 12, vertex_buffer_dataL, color, GL_FILL);

    static const GLfloat vertex_buffer_dataM[] = {
        0.4f, -0.2f, 0.0f,
        0.4f, 0.2f, 0.0f,
        0.5f, 0.0f, 0.0f,

        -0.4f, -0.2f, 0.0f,
        -0.4f, 0.2f, 0.0f,
        -0.5f, 0.0f, 0.0f,

        0.4f, 0.2f, 0.0f,
        0.4f, -0.2f, 0.0f,
        -0.4f, -0.2f, 0.0f,

        0.4f, 0.2f, 0.0f,
        -0.4f, 0.2f, 0.0f,
        -0.4f, -0.2f, 0.0f,
    };
    this->object[6] = create3DObject(GL_TRIANGLES, 12, vertex_buffer_dataM, color, GL_FILL);

    static const GLfloat vertex_buffer_dataRU[] = {
        0.5f, 0.5f, 0.0f,
        0.4f, 0.4f, 0.0f,
        0.5f, 0.4f, 0.0f,

        0.5f, 0.0f, 0.0f,
        0.6f, 0.2f, 0.0f,
        0.4f, 0.2f, 0.0f,

        0.6f, 0.4f, 0.0f,
        0.4f, 0.4f, 0.0f,
        0.4f, 0.2f, 0.0f,

        0.4f, 0.2f, 0.0f,
        0.6f, 0.2f, 0.0f,
        0.6f, 0.4f, 0.0f,
    };
    this->object[1] = create3DObject(GL_TRIANGLES, 12, vertex_buffer_dataRU, color, GL_FILL);

    static const GLfloat vertex_buffer_dataRL[] = {
        0.5f, -0.5f, 0.0f,
        0.4f, -0.4f, 0.0f,
        0.5f, -0.4f, 0.0f,

        0.5f, 0.0f, 0.0f,
        0.6f, -0.2f, 0.0f,
        0.4f, -0.2f, 0.0f,

        0.6f, -0.4f, 0.0f,
        0.4f, -0.4f, 0.0f,
        0.4f, -0.2f, 0.0f,

        0.4f, -0.2f, 0.0f,
        0.6f, -0.2f, 0.0f,
        0.6f, -0.4f, 0.0f,
    };
    this->object[2] = create3DObject(GL_TRIANGLES, 12, vertex_buffer_dataRL, color, GL_FILL);

    static const GLfloat vertex_buffer_dataLU[] = {
        -0.5f, 0.5f, 0.0f,
        -0.4f, 0.4f, 0.0f,
        -0.5f, 0.4f, 0.0f,

        -0.5f, 0.0f, 0.0f,
        -0.6f, 0.2f, 0.0f,
        -0.4f, 0.2f, 0.0f,

        -0.6f, 0.4f, 0.0f,
        -0.4f, 0.4f, 0.0f,
        -0.4f, 0.2f, 0.0f,

        -0.4f, 0.2f, 0.0f,
        -0.6f, 0.2f, 0.0f,
        -0.6f, 0.4f, 0.0f,
    };
    this->object[5] = create3DObject(GL_TRIANGLES, 12, vertex_buffer_dataLU, color, GL_FILL);

    static const GLfloat vertex_buffer_dataLL[] = {
        -0.5f, -0.5f, 0.0f,
        -0.4f, -0.4f, 0.0f,
        -0.5f, -0.4f, 0.0f,

        -0.5f, 0.0f, 0.0f,
        -0.6f, -0.2f, 0.0f,
        -0.4f, -0.2f, 0.0f,

        -0.6f, -0.4f, 0.0f,
        -0.4f, -0.4f, 0.0f,
        -0.4f, -0.2f, 0.0f,

        -0.4f, -0.2f, 0.0f,
        -0.6f, -0.2f, 0.0f,
        -0.6f, -0.4f, 0.0f,
    };
    this->object[4] = create3DObject(GL_TRIANGLES, 12, vertex_buffer_dataLL, color, GL_FILL);
}

void Score::draw(glm::mat4 VP, int digit)
{
    std::string characters[10];
    characters[0] = "1111110";
    characters[1] = "0110000";
    characters[2] = "1101101";
    characters[3] = "1111001";
    characters[4] = "0110011";
    characters[5] = "1011011";
    characters[6] = "0011111";
    characters[7] = "1110000";
    characters[8] = "1111111";
    characters[9] = "1110011";

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    for(int i=0; i<7; ++i)
    {
        if(characters[digit][i] == '1')
        {
            draw3DObject(this->object[i]);
        }
    }
}

void Score::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Score::print_score(long long int score, glm::mat4 VP)
{
    if(score == 0)
    {
        Score::draw(VP, 0);
    }
    while (score != 0)
    {
        int digit = score % 10;
        Score::draw(VP, digit);
        this->position.x -= 1.4;
        score /= 10;
    }
}

void Score::tick()
{

}
