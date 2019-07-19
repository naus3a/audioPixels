#version 330

// ping pong inputs
uniform sampler2DRect particles0;
uniform sampler2DRect particles1;
uniform sampler2DRect texStartPos;

uniform vec3 mouse;
uniform float radiusSquared;
uniform float elapsed;

in vec2 texCoordVarying;

layout(location = 0) out vec4 posOut;
layout(location = 1) out vec4 velOut;

/*void calcAttraction(in vec3 _posAttractor, in vec3 _pos, in float _rSq, out vec3 _frc){
    vec3 dir = _posAttractor - _pos;
    float distSq = dot(dir, dir);
    float mag = 500.0 * (1.0-distSq/_rSq);
    _frc = step(distSq, _rSq)*mag*normalize(dir);
}*/

vec3 getAttractionForce(in float _distSq, in float _rSq, in vec3 _dir){
    float mag = 500.0 * (1.0-distSq/_rSq);
    vec3 frc = step(_distSq, _rSq)*mag*_dir;
}

bool updateAttractor(in vec3 _posAttractor, in vec3 _pos, float _rSq){
    vec3 diff = _posAttractor - _pos;
    float distSq = dot(diff, diff);
    if(distSq<_rSq){
        vec3 force = getAttractionForce(distSq, _rSq, normalize(diff));
        force += vec3(0.0, -0.5, 0.0);
    }else{
        return false;
    }
}

void main()
{
    vec3 pos = texture(particles0, texCoordVarying.st).xyz;
    vec3 vel = texture(particles1, texCoordVarying.st).xyz;
    
    
    
    //vec3 force;
    //calcAttraction(mouse, pos.xyz, radiusSquared, force);
    
    // gravity
    force += vec3(0.0, -0.5, 0.0);
    
    // accelerate
    vel += elapsed * force;
    
    // bounce off the sides
    vel.x *= step(abs(pos.x), 512.0) * 2.0 - 1.0;
    vel.y *= step(abs(pos.y), 384.0) * 2.0 - 1.0;
    
    // damping
    vel *= 0.995;
    
    // move
    pos += elapsed * vel;
    
    posOut = vec4(pos, 1.0);
    velOut = vec4(vel, 0.0);
}
