#pragma once


/*
Example

auto BlueSquare = ECS::entity()
    .set<Color>({0, 0, 255})
    .set<Square>({50});

auto SquareA = ECS::entity()
    .add_instanceof(BlueSquare)
    .set<Position>({10, 20});

auto SquareB = ECS::entity()
    .add_instanceof(BlueSquare)
    .set<Position>({30, 40});


    entity - int id
    map of entity and vector of component (id)
    component / type - int id
    map of component id and vector of component (id) ????


    component array
    entity, component


    system
    entity


*/
