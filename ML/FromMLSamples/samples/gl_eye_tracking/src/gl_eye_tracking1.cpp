#include "gl_eye_tracking/gl_eye_tracking1.hpp"

const glm::vec3 kCubeScale = glm::vec3(0.01f, 0.01f, 0.01f);

void GLEyeTrackingApp::OnStart()
{
  ML_LOG(Info, "OnStart()");


  tex_            = ml::app_framework::Registry::GetInstance()->GetResourcePool()->LoadTexture("data/Controller.fbm/Controller.png", GL_SRGB8_ALPHA8);

  fixation_node_  = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Cube);
  left_gaze_node_ = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Line);
  quad_node_      = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Quad);
  // tex_node_       = ml::app_framework::CreatePresetNode(ml::app_framework::NodeType::Quad);
  tex_node_       = std::make_shared<ml::app_framework::Node>();


  aiMesh *ai_mesh;
  aiVector3D mVertices { 0.000167909704, 0.768751860, 2.03365755 };
  aiVector3D mNormals  { 0.00000002614023, 0.931566238, 0.363571823 };



  ai_mesh->mPrimitiveTypes = GL_TRIANGLES;
  ai_mesh->mNumVertices = 4;
  ai_mesh->mNumFaces = 7194;
  ai_mesh->mVertices = &mVertices;
  ai_mesh->mNormals = &mNormals;

  // ai_mesh->mVertices = &mVertices;
  const aiTexture *ai_tex = nullptr;
  std::string texture_full_name;
  bool embedded_texture = false;
  
  std::shared_ptr<ml::app_framework::PBRMaterial> mat = 
    std::make_shared<ml::app_framework::PBRMaterial>();


  mat->SetAlbedo(tex_);
  mat->SetHasAlbedo(true);

  ml::app_framework::Model model;
  model.material = mat;
  auto renderable_pbr = std::make_shared<ml::app_framework::RenderableComponent>(model.mesh, model.material);

  
  tex_node_->AddComponent(renderable_pbr);


  GetRoot()->AddChild(fixation_node_);
  GetRoot()->AddChild(left_gaze_node_);
  GetRoot()->AddChild(quad_node_);
  GetRoot()->AddChild(tex_node_);

  fixation_node_->SetLocalScale(kCubeScale);
  quad_node_->SetLocalScale(kCubeScale);
}

void GLEyeTrackingApp::OnStop()
{
  ML_LOG(Info, "OnStop()");
}

void GLEyeTrackingApp::OnUpdate(float)
{
  // ML_LOG(Info, "-------------");
  // ML_LOG(Info, "OnUpdate()");


  const glm::quat Q_W(-0.0, 0.0, -0.0, 1.0);
  const glm::vec3 P_W(-0.0, -0.0, -0.5);
  const glm::vec3 left_direction(0.0, 0.0, -1.0);

  fixation_node_->SetWorldRotation(Q_W);
  fixation_node_->SetWorldTranslation(P_W);

  quad_node_->SetWorldRotation(Q_W);
  quad_node_->SetWorldTranslation(P_W);

  glm::vec3 left_gaze_line[] = {
    P_W,
    P_W + left_direction
  };

  auto left_line_renderable = left_gaze_node_->GetComponent<ml::app_framework::RenderableComponent>();
  left_line_renderable->GetMesh()->SetPrimitiveType(GL_LINES);
  left_line_renderable->GetMesh()->UpdateMesh(left_gaze_line, nullptr, sizeof(left_gaze_line)/sizeof(glm::vec3), nullptr, 0);
  auto left_line_material = 
      std::static_pointer_cast<ml::app_framework::FlatMaterial>(left_line_renderable->GetMaterial());
  left_line_material->SetColor(glm::vec4(.0f, .0f, 1.0f, 1.0f));



  // const glm::vec3 *vertices = nullptr;
  // const glm::vec3 *normals = nullptr;

  // vertices = (const glm::vec3 *)ai_mesh->mVertices;
  // num_vertices = ai_mesh->mNumVertices;

  // std::vector<uint32_t> indices;
  // size_t num_vertices = 0;



  glm::vec3 tex_vertices[] = {
    glm::vec3(0.5f,  0.5f, 0.0f),  // top right
    glm::vec3(0.5f, -0.5f, 0.0f),  // bottom right
    glm::vec3(-0.5f, -0.5f, 0.0f),  // bottom left
    glm::vec3(-0.5f,  0.5f, 0.0f)   // top left 
  }; 


  // unsigned int indices[] = {  // note that we start from 0!
  //   0, 1, 3,   // first triangle
  //   1, 2, 3    // second triangle
  // };

  glm::vec3 tex_indices[] = {
    glm::vec3(0, 1, 3),
    glm::vec3(1, 2, 3),
  };


  // mesh->UpdateMesh(vertices, normals, ai_mesh->mNumVertices, indices.data(), indices.size());
  // if (ai_mesh->HasTextureCoords(0)) {
  //   std::vector<glm::vec2> tex_coords(ai_mesh->mNumVertices);
  //   for (uint32_t i = 0; i < ai_mesh->mNumVertices; ++i) {
  //     tex_coords[i].x = ai_mesh->mTextureCoords[0][i].x;
  //     tex_coords[i].y = ai_mesh->mTextureCoords[0][i].y;
  //   }
  //   mesh->UpdateTexCoordsBuffer((glm::vec2 const *)tex_coords.data());
  // }

  // mesh_cache_.insert(std::make_pair(path, mesh));
  // model.mesh = mesh;

  // auto tex_renderable = tex_node_->GetComponent<ml::app_framework::RenderableComponent>();
  // tex_renderable->GetMesh()->SetPrimitiveType(GL_TRIANGLES);
  // tex_renderable->GetMesh()->UpdateMesh(tex_indices, 
  //   nullptr, sizeof(tex_indices)/sizeof(glm::vec3), tex_vertices, sizeof(tex_vertices) / sizeof(glm::vec3));
  // auto left_line_material = 
  //     std::static_pointer_cast<ml::app_framework::FlatMaterial>(left_line_renderable->GetMaterial());
  // left_line_material->SetColor(glm::vec4(.0f, .0f, 1.0f, 1.0f));


}

int main(int argc, char **argv) {
  GLEyeTrackingApp app(argc, argv);
  app.SetUseGfx(true);
  app.RunApp();
  return 0;
}
