#include <lighting.h>
#include <shape.h>

point_light make_point_light(tuple position, tuple intensity) {
	point_light light;
	light.position = position;
	light.intensity = intensity;
	return light;
}

tuple lighting_color(shape* object, material_properties mat, point_light light, tuple pt, tuple eyev, tuple normal, bool in_shadow) {

	tuple ambient, diffuse, specular;
	tuple black = color(0, 0, 0);

	tuple base_color;
	if(object->has_pattern == true)
		base_color = pattern_at_object(object->pattern, object, pt);
	else
		base_color = mat.color;

	tuple effective_color = hadamard(light.intensity, base_color);
	ambient = mul(effective_color, mat.ambient);


	tuple lightv = normalize(sub(light.position, pt));
	float light_cos = dot(normal, lightv);
	if(in_shadow == true || light_cos <= 0)
		diffuse = black;
	else 
		diffuse = mul(effective_color, (light_cos * mat.diffuse));


	if(in_shadow == true || light_cos <= 0)
		specular = black;
	else {
		tuple reflectv = find_reflection(neg(lightv), normal);
		float reflect_cos = dot(reflectv, eyev);
		if(reflect_cos <= 0)
			specular = black;
		else {
			float spec_factor = pow(reflect_cos, mat.shininess);
			specular = mul(light.intensity, (spec_factor * mat.specular));
		}
	}

	tuple final = add(ambient, add(diffuse, specular));
	return final;
}


tuple find_reflection(tuple in, tuple normal) {
	float component = dot(in, normal);
	return add(in, mul(normal, -2 * component));
}
