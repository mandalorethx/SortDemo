//
// Created by matt on 5/20/16.
//

#include "SortDemoRenderer.h"
#include "SDShaders.h"

SortDemoRenderer::SortDemoRenderer() {
    m_nWidth = 0;
    m_nHeight = 0;
}

SortDemoRenderer::~SortDemoRenderer() {

}

bool32 SortDemoRenderer::CreateRenderer(uint32 nWidth, uint32 nHeight) {
    m_nWidth = nWidth;
    m_nHeight = nHeight;

    SDPipeline::TPipelineInfo pipelineInfo = { SDShaders::VertexShader, SDShaders::FragmentShader };
    m_pipeline.Create(&pipelineInfo);

}

bool32 SortDemoRenderer::AddMesh(const char* pszMeshFile) {
    SDMesh::TMeshInfo meshInfo = {pszMeshFile};
    SDMesh* pNewMesh = new SDMesh();
    bool32 bSuccess = pNewMesh->Create(&meshInfo);
    m_meshStack.PushBack(pNewMesh);
    return bSuccess;
}

void   SortDemoRenderer::DrawFrame() {
    glViewport(0, 0, m_nWidth, m_nHeight); CHECKGL;
    m_pipeline.Start();
    for (uint32 nMesh = 0; nMesh < m_meshStack.GetNumElements(); ++nMesh) {
        SOFT_CAST(SDMesh*, m_meshStack.GetItem(nMesh))->Draw();
    }
    m_pipeline.End();
}

void   SortDemoRenderer::DestroyRenderer() {
    m_pipeline.Destroy();
    uint32 nMeshCount = m_meshStack.GetNumElements();
    for (uint32 nMesh = 0; nMesh < nMeshCount; ++nMesh) {
        SOFT_CAST(SDMesh*, m_meshStack.GetBack())->Destroy();
        m_meshStack.RemoveBack();
    }
}

SortDemoRenderer* pRenderer = NULL;

extern "C" {
    JNIEXPORT void JNICALL Java_com_example_matt_sortdemo_SortDemoRenderer_create_renderer(JNIEnv * env, jobject obj,  jint width, jint height);
    JNIEXPORT void JNICALL Java_com_example_matt_sortdemo_SortDemoRenderer_destroy_renderer(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_example_matt_sortdemo_SortDemoRenderer_draw_frame(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_example_matt_sortdemo_SortDemoRenderer_add_mesh(JNIEnv * env, jobject obj, const char* pszMeshFile);
};

JNIEXPORT void JNICALL Java_com_example_matt_sortdemo_SortDemoRenderer_create_renderer(JNIEnv * env, jobject obj,  jint width, jint height)
{
    pRenderer = new SortDemoRenderer();
    pRenderer->CreateRenderer(width, height);
}

JNIEXPORT void JNICALL Java_com_example_matt_sortdemo_sort_demo_shared_destroy_renderer(JNIEnv * env, jobject obj)
{
    if (pRenderer != NULL) {
        pRenderer->DestroyRenderer();
        delete pRenderer;
        pRenderer = NULL;
    }
}

JNIEXPORT void JNICALL Java_com_example_matt_sortdemo_sort_demo_shared_draw_frame(JNIEnv * env, jobject obj)
{
    pRenderer->DrawFrame();
}

JNIEXPORT void JNICALL Java_com_example_matt_sortdemo_sort_demo_shared_add_mesh(JNIEnv * env, jobject obj, jstring pszMeshFile)
{
    const char* pszCMeshFile = (env)->GetStringUTFChars(pszMeshFile, NULL);
    pRenderer->AddMesh(pszCMeshFile);
}

