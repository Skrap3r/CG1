#ifndef CGSCENECONTROL_H
#define CGSCENECONTROL_H

#include "CgBase/CgObserver.h"
#include "CgBase/CgBaseSceneControl.h"
#include <glm/glm.hpp>
#include <vector>
#include "CgScenegraph.h"

class CgBaseEvent;
class CgBaseRenderer;
class CgExampleTriangle;
class CgDice;
class CgPolyline;
class CgRotation;

class CgSceneControl : public CgObserver, public CgBaseSceneControl
{
public:
    CgSceneControl();

    void Uebung05();
    void Uebung04();

    ~CgSceneControl();
    void handleEvent(CgBaseEvent* e);
    void setRenderer(CgBaseRenderer* r);

    void renderObjects();

    void setCurrent_transformation(const glm::mat4 &current_transformation);
    void setCurrentMatrix();

    void iterate_graph(CgSceneGraphEntity* arg_child, glm::vec3 arg_color);

    void scale_obj(CgSceneGraphEntity* arg_entity, glm::vec3 arg_scale);
    void translate_obj(CgSceneGraphEntity* arg_entity, glm::vec3 arg_translation);
    void rotate_obj(CgSceneGraphEntity* arg_entity, glm::vec3 arg_rotation, float arg_angle);
private:
    CgBaseRenderer* m_renderer;

    CgExampleTriangle* m_triangle;
    CgDice* m_dice;
    CgPolyline* m_polyline;
    CgRotation* m_rotation;

    CgPolyline* m_localX;
    CgPolyline* m_localY;
    CgPolyline* m_localZ;

    CgScenegraph* graph;

    //Uebung 05 Schachscene
    CgDice* m_person;
    CgDice* m_rook;
    CgDice* m_bishop;
    CgDice* m_knight;
    CgDice* m_king;
    CgDice* m_queen;

    CgSceneGraphEntity* root;
    CgSceneGraphEntity* root_table;
    CgSceneGraphEntity* root_chair;
    CgSceneGraphEntity* root_board;
    CgSceneGraphEntity* root_chest;
    CgSceneGraphEntity* root_chessPieces;
    CgSceneGraphEntity* root_chessPawns;

    CgSceneGraphEntity* tableplate;
    CgSceneGraphEntity* leg_1;
    CgSceneGraphEntity* leg_2;
    CgSceneGraphEntity* leg_3;
    CgSceneGraphEntity* leg_4;

    CgSceneGraphEntity* chessBoard;
    CgSceneGraphEntity* t1_king;
    CgSceneGraphEntity* t1_queen;
    CgSceneGraphEntity* t1_knight1;
    CgSceneGraphEntity* t1_knight2;
    CgSceneGraphEntity* t1_bishop1;
    CgSceneGraphEntity* t1_bishop2;
    CgSceneGraphEntity* t1_rook1;
    CgSceneGraphEntity* t1_rook2;
    CgSceneGraphEntity* t1_pawn_1;
    CgSceneGraphEntity* t1_pawn_2;
    CgSceneGraphEntity* t1_pawn_3;
    CgSceneGraphEntity* t1_pawn_4;
    CgSceneGraphEntity* t1_pawn_5;
    CgSceneGraphEntity* t1_pawn_6;
    CgSceneGraphEntity* t1_pawn_7;
    CgSceneGraphEntity* t1_pawn_8;

    CgSceneGraphEntity* t2_king;
    CgSceneGraphEntity* t2_queen;
    CgSceneGraphEntity* t2_knight1;
    CgSceneGraphEntity* t2_knight2;
    CgSceneGraphEntity* t2_bishop1;
    CgSceneGraphEntity* t2_bishop2;
    CgSceneGraphEntity* t2_rook1;
    CgSceneGraphEntity* t2_rook2;
    CgSceneGraphEntity* t2_pawn_1;
    CgSceneGraphEntity* t2_pawn_2;
    CgSceneGraphEntity* t2_pawn_3;
    CgSceneGraphEntity* t2_pawn_4;
    CgSceneGraphEntity* t2_pawn_5;
    CgSceneGraphEntity* t2_pawn_6;
    CgSceneGraphEntity* t2_pawn_7;
    CgSceneGraphEntity* t2_pawn_8;

    CgSceneGraphEntity* chestFloor;
    CgSceneGraphEntity* chestWall_1;
    CgSceneGraphEntity* chestWall_2;
    CgSceneGraphEntity* chestWall_3;
    CgSceneGraphEntity* chestWall_4;

    CgSceneGraphEntity* chairSeat;
    CgSceneGraphEntity* seatRest;
    CgSceneGraphEntity* seatLeg_1;
    CgSceneGraphEntity* seatLeg_2;
    CgSceneGraphEntity* seatLeg_3;
    CgSceneGraphEntity* seatLeg_4;
    CgSceneGraphEntity* person;



    CgSceneGraphEntity* root1;
    CgSceneGraphEntity* root2;
    CgSceneGraphEntity* e1;
    CgSceneGraphEntity* e2;
    CgSceneGraphEntity* e3;
    CgSceneGraphEntity* e4;

    CgSceneGraphEntity* eX;
    CgSceneGraphEntity* eY;
    CgSceneGraphEntity* eZ;

    CgSceneGraphEntity* current_Entity;

    std::vector<CgPolyline*> m_normalsRotation;

    glm::mat4 m_current_transformation;
    glm::mat4 m_trackball_rotation;
    glm::mat4 m_lookAt_matrix;
    glm::mat4 m_proj_matrix;

    int count;
    glm::vec4 old_color;
};

#endif // CGSCENECONTROL_H
