#include <LightManager.h>

using namespace std;

float LightManager::movementSpeed = 5.0f;
const glm::vec3 LightManager::LEFT  = glm::vec3(1, 0, 0);
const glm::vec3 LightManager::UP    = glm::vec3(0, 1, 0);
const glm::vec3 LightManager::FRONT = glm::vec3(0, 0, 1);

void LightManager::switchToNext()
{
    switch (activeType)
    {
        case ActiveLightType::NONE:
        {
            return;
        }
        case ActiveLightType::POINT:
        {
            if (m_pointLights.size() > 0)
            {
                curPointLight = (curPointLight + 1) % m_pointLights.size();
            }
            break;
        }
        case ActiveLightType::SPOT:
        {
            if (m_spotLights.size() > 0)
            {
                curSpotLight = (curSpotLight + 1) % m_spotLights.size();
            }
            break;
        }
        case ActiveLightType::DIRECTIONAL:
        {
            if (m_directionalLights.size() > 0)
            {
                curDirectionalLight = (curDirectionalLight + 1) % m_directionalLights.size();
            }
            break;
        }
    }
}

void LightManager::switchToPrevious()
{
    switch (activeType)
    {
        case ActiveLightType::NONE:
        {
            return;
        }
        case ActiveLightType::POINT:
        {
            if (m_spotLights.size() > 0)
            {
                curPointLight = curPointLight == 0 ? m_pointLights.size() - 1 : (curPointLight - 1) % m_pointLights.size();
            }
            break;
        }
        case ActiveLightType::SPOT:
        {
            if (m_spotLights.size() > 0)
            {
                curSpotLight = curSpotLight == 0 ? m_spotLights.size() - 1 : (curSpotLight - 1) % m_spotLights.size();
            }
            break;
        }
        case ActiveLightType::DIRECTIONAL:
        {
            if (m_directionalLights.size() > 0)
            {
                curDirectionalLight = curDirectionalLight == 0 ? m_spotLights.size() - 1 : (curDirectionalLight - 1) % m_spotLights.size();
            }
            break;
        }
    }
}

void LightManager::switchLightType(ActiveLightType type)
{    
    if (activeType == type)
        activeType = ActiveLightType::NONE;
    else
        activeType = type;
}

void LightManager::translateCurrentLight(Direction dir)
{
    if (activeType == ActiveLightType::NONE ||
        (activeType == ActiveLightType::POINT && m_pointLights.size() == 0) ||
        (activeType == ActiveLightType::SPOT && m_spotLights.size() == 0))
    {
        return;
    }
    
    glm::vec3 delta;
    switch (dir)
    {
    case Direction::UP:
        delta = UP;
        break;
    case Direction::DOWN:
        delta = -UP;
        break;
    case Direction::FRONT:
        delta = FRONT;
        break;
    case Direction::BACK:
        delta = -FRONT;
        break;
    case Direction::LEFT:
        delta = LEFT;
        break;
    case Direction::RIGHT:
        delta = -LEFT;
        break;
    }
    delta *= movementSpeed * deltaTime;

    if (activeType == ActiveLightType::POINT)
    {
        m_pointLights[curPointLight].setPosition(m_pointLights[curPointLight].getPosition() + delta);
    }
    else if (activeType == ActiveLightType::SPOT)
    {
        m_spotLights[curSpotLight].setPosition(m_spotLights[curSpotLight].getPosition() + delta);
    }
}

void LightManager::switchLightState()
{
    if (activeType == ActiveLightType::NONE ||
       (activeType == ActiveLightType::POINT && m_pointLights.size() == 0) ||
       (activeType == ActiveLightType::SPOT && m_spotLights.size() == 0) ||
       (activeType == ActiveLightType::DIRECTIONAL && m_directionalLights.size() == 0))
    {
        return;
    }
    switch (activeType)
    {
        case ActiveLightType::POINT:
        {
            m_pointLights[curPointLight].switchState();
        }
        break;
        case ActiveLightType::SPOT:
        {
            m_spotLights[curSpotLight].switchState();
        }
        break;
        case ActiveLightType::DIRECTIONAL:
        {
            m_directionalLights[curDirectionalLight].switchState();
        }
        break;
    }
}

void LightManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // lights control
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        switchLightType(ActiveLightType::POINT);
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        switchLightType(ActiveLightType::SPOT);
    }
    if (key == GLFW_KEY_3 && action == GLFW_PRESS)
    {
        switchLightType(ActiveLightType::DIRECTIONAL);
    }
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    {
        switchToPrevious();
    }
    if (key == GLFW_KEY_RIGHT&& action == GLFW_PRESS)
    {
        switchToNext();
    }
    if (key == GLFW_KEY_U && action == GLFW_REPEAT)
    {
        translateCurrentLight(Direction::UP);
    }
    if (key == GLFW_KEY_O && action == GLFW_REPEAT)
    {
        translateCurrentLight(Direction::DOWN);
    }
    if (key == GLFW_KEY_I && action == GLFW_REPEAT)
    {
        translateCurrentLight(Direction::FRONT);
    }
    if (key == GLFW_KEY_K && action == GLFW_REPEAT)
    {
        translateCurrentLight(Direction::BACK);
    }
    if (key == GLFW_KEY_J && action == GLFW_REPEAT)
    {
        translateCurrentLight(Direction::LEFT);
    }
    if (key == GLFW_KEY_L && action == GLFW_REPEAT)
    {
        translateCurrentLight(Direction::RIGHT);
    }
    if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS)
    {
        movementSpeed = movementSpeed >= 10.0f ? 10.0f : movementSpeed + 1.0f;
    }
    if (key == GLFW_KEY_MINUS && action == GLFW_PRESS)
    {
        movementSpeed = movementSpeed <= 0.0f ? 0.0f : movementSpeed - 1.0f;
    }
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        switchLightState();
    }
}