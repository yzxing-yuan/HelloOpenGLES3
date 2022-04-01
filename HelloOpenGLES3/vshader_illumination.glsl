#version 300 es

// 平行光属性
struct directional_light
{
    vec3 direction;  // 在眼睛内的照明方向
    vec3 halfplane;  // 规范化的半平面向量H。对于直射光可以预先计算，因为它不会变化
    vec4 ambient_color;  // 环境光颜色
    vec4 diffuse_color;  // 漫射光颜色
    vec4 specular_color;  // 反射光颜色
};

// 材料属性
struct material_properties
{
    vec4 ambient_color;  // 材料的环境颜色
    vec4 diffuse_color;  // 材料的漫射颜色
    vec4 specular_color;  // 材料的反射颜色
    float specular_exponent;  // 描述材料光亮度的反光指数，用于控制反射高光的亮度
};

const float c_zero = 0.0;
const float c_one = 1.0;

uniform mat4 u_mvpMatrix;
uniform material_properties material;
uniform directional_light light;

vec4 directional_light_color(vec3 normal)
{
    vec4 computed_color = vec4(c_zero, c_zero, c_zero, c_zero);
    float ndotl;
    float ndoth;

    ndotl = max(c_zero, dot(normal, light.direction));
    ndoth = max(c_zero, dot(normal, light.halfplane));

    computed_color += (light.ambient_color * material.ambient_color);
    computed_color += (light.diffuse_color * material.diffuse_color);
    if(ndoth > c_zero)
    {
        computed_color += (pow(ndoth, material.specular_exponent) * material.specular_color * light.specular_color);
    }

    return computed_color;
}

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec3 a_normal;

out vec4 v_color;

void main(void)
{
    v_color = directional_light_color(a_normal);
    gl_Position = u_mvpMatrix * a_position;
}
