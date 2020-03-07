#ifndef LIGHT_MANAGER_H
#define LIGHT_MANAGER_H

#include <vector>
#include <map>
#include <Aliases.h>
#include <Lights/PointLight.h>
#include <Lights/SpotLight.h>
#include <GLFW/glfw3.h>

enum class ActiveLightType 
{
    NONE,
    POINT,
    SPOT,
	DIRECTIONAL,
	SUN
};

enum class Direction
{
    UP,
    DOWN,
    FRONT,
    BACK,
    LEFT,
    RIGHT
};

enum class TimeOfDay
{
	MORNING,
	MIDDAY,
	EVENING,
	NIGHT
};



class LightManager 
{ 
    static float movementSpeed;
    static const glm::vec3 LEFT;
    static const glm::vec3 UP;
    static const glm::vec3 FRONT;
	static std::map<TimeOfDay, TimeOfDay> nextTimeOfDay;

public:
    LightManager(PointLights& pointLights, SpotLights& spotLights, DirectionalLights& directionalLights, DirectionalLight& sun) 
		: m_pointLights(pointLights)
		, m_spotLights(spotLights)
		, m_directionalLights(directionalLights)
		, m_sun(sun) {};

    void switchToNext();
    void switchToPrevious();
    void switchLightType(ActiveLightType type);
    void translateCurrentLight(Direction dir);
	void switchLightState();
    void setActiveLightType(ActiveLightType type) { this->activeType = type; }
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void updateDeltaTime(float deltaTime) { this->deltaTime = deltaTime >= 0 ? deltaTime : 0; }

private:
	void switchTimeOfDay();

private:    
    PointLights& m_pointLights;
    SpotLights& m_spotLights;
	DirectionalLights& m_directionalLights;

	DirectionalLight& m_sun;
	TimeOfDay m_timeOfDay = TimeOfDay::MORNING;

    int curPointLight = 0;
    int curSpotLight = 0;
	int curDirectionalLight = 0;

    ActiveLightType activeType = ActiveLightType::NONE;
    float deltaTime = 0;
};

#endif // !LIGHT_MANAGER_H
