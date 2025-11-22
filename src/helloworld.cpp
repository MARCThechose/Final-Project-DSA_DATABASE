#include <iostream>
#include <vector>
#include <string>

#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

struct AdminData {
    int id;
    std::string name;
    std::string username;
    std::string password;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "what the helly: no window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSwapInterval(1);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    sql::Connection* con = nullptr;
    try {
        sql::Driver* driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306/Container_Inv_Sys", "root", "FORGETpassword1");
        std::cout << "Connection successful!" << std::endl;
    }
    catch (sql::SQLException& e)
    {
        std::cout << "SQL Error: " << e.what() << std::endl;
        return -1;
    }

    static int queryCounter = 0;
    std::vector<AdminData> adminData;
    bool querySuccess = false;

    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }

        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (con && queryCounter++ % 60 == 0)
        {
            sql::Statement* stmt = nullptr;
            sql::ResultSet* res = nullptr;
            try
            {
                stmt = con->createStatement();
                res = stmt->executeQuery("SELECT * FROM Admin");
                querySuccess = true;

                adminData.clear();
                while (res->next())
                {
                    adminData.push_back({
                        res->getInt("Admin_ID"),
                        res->getString("Name").c_str(),
                        res->getString("Username").c_str(),
                        res->getString("Password").c_str()
                        });
                }
            }
            catch (sql::SQLException& e)
            {
                std::cout << "SQL Error during query: " << e.what() << std::endl;
                querySuccess = false;
            }
            delete res;
            delete stmt;
        }

        ImGui::Begin("Admin Data");

        if (querySuccess && !adminData.empty())
        {
            if (ImGui::BeginTable("AdminTable", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
            {
                ImGui::TableSetupColumn("Admin_ID");
                ImGui::TableSetupColumn("Name");
                ImGui::TableSetupColumn("Username");
                ImGui::TableSetupColumn("Password");
                ImGui::TableHeadersRow();

                for (const auto& data : adminData)
                {
                    ImGui::TableNextRow();

                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text("%d", data.id);

                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text("%s", data.name.c_str());

                    ImGui::TableSetColumnIndex(2);
                    ImGui::Text("%s", data.username.c_str());

                    ImGui::TableSetColumnIndex(3);
                    ImGui::Text("%s", data.password.c_str());
                }
                ImGui::EndTable();
            }
        }
        else {
            ImGui::Text("No data available or query failed.");
        }
        ImGui::End();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    if (con) delete con;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}