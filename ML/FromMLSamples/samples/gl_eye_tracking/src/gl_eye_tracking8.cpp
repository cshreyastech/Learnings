#include "gl_eye_tracking/gl_eye_tracking8.hpp"

void GLEyeTrackingApp::OnStart()
{
  ML_LOG(Info, "OnStart()");

  std::shared_ptr<Mesh> quad = Registry::GetInstance()->GetResourcePool()->GetMesh<QuadMesh>();


  // int32_t channels = 0;
  // GLuint gl_texture = 0;
  // int32_t width = 0;
  // int32_t height = 0;

  // unsigned char *buffer = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);


  // load and create a texture 
  // -------------------------
  
  glGenTextures(1, &texture);
  glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
  glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load image, create texture and generate mipmaps
  int width, height, nrChannels;
  // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
  // unsigned char *data = stbi_load(FileSystem::getPath("../src/res/texture/container.jpg").c_str(), &width, &height, &nrChannels, 0);
  unsigned char *data = stbi_load("data/res/texture/container.jpg", &width, &height, &nrChannels, 0);

  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    ML_LOG(Info,"Failed to load texture");
  }
  
  stbi_image_free(data);
  off_screen_texture_ = std::make_shared<Texture>(GL_TEXTURE_2D, texture, width, height, true);

  // glBindFramebuffer(GL_READ_FRAMEBUFFER, (GLuint)imgui_frame_buffer);
  // glBindFramebuffer(GL_DRAW_FRAMEBUFFER, blit_target->GetGLFramebuffer());
  // glBlitFramebuffer(0, 0, imgui_texture->GetWidth(), imgui_texture->GetHeight(), blit_target->GetWidth() / 2, 0,
  // blit_target->GetWidth(), blit_target->GetHeight() / 2, GL_COLOR_BUFFER_BIT, GL_LINEAR);



  // off_screen_texture_ = Registry::GetInstance()->GetResourcePool()->LoadTexture("data/res/texture/container.jpg", GL_RGB);
  std::shared_ptr<TexturedMaterial> gui_mat = std::make_shared<TexturedMaterial>(off_screen_texture_);
  // gui_mat->EnableAlphaBlending(true);
  std::shared_ptr<RenderableComponent> gui_renderable = std::make_shared<RenderableComponent>(quad, gui_mat);
  gui_node_ = std::make_shared<Node>();
  gui_node_->AddComponent(gui_renderable);

  GetRoot()->AddChild(gui_node_);

}

void GLEyeTrackingApp::OnStop()
{
  ML_LOG(Info, "OnStop()");

}

void GLEyeTrackingApp::OnUpdate(float)
{
  ML_LOG(Info, "OnUpdate()");

  const glm::quat Q_W(-0.0, 0.0, -0.0, 1.0);
  const glm::vec3 P_W(-0.0, -0.0, -0.5);
  glBindTexture(GL_TEXTURE_2D, texture);
  
  gui_node_->SetWorldRotation(Q_W);
  gui_node_->SetWorldTranslation(P_W);
}

int main(int argc, char **argv) {
  GLEyeTrackingApp app(argc, argv);
  app.SetUseGfx(true);
  app.RunApp();
  return 0;
}
