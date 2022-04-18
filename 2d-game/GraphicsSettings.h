#ifndef GRAPHICSSETTINGS_H
#define GRAPHICSSETTINGS_H

class GraphicsSettings {
private:
    
public:
    GraphicsSettings();
    // Variables
    std::string title;
    VideoMode resolution;
    bool fullscreen;
    bool verticalSync;
    unsigned frameRateLimit;
    ContextSettings contextSettings;
    std::vector<VideoMode> videoModes;

    // Functions

    void saveToFile(const std::string path);

    void loadFromFile(const std::string path);
};

#endif