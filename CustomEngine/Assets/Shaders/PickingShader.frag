#version 330 core
layout(location = 0) out uint outID;

uniform uint u_EntityID;

void main()
{
    outID = u_EntityID;
}
