/*
 * GL_exart_function.cpp
 *
 *  Created on: Jun 9, 2010
 *      Author: rolf
 */
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glfw.h>
#include "GL_extart_functions.h"
#include <iostream>
PFNGLISRENDERBUFFEREXTPROC glIsRenderbufferEXT = NULL;
PFNGLBINDRENDERBUFFEREXTPROC glBindRenderbufferEXT = NULL;
PFNGLDELETERENDERBUFFERSEXTPROC glDeleteRenderbuffersEXT = NULL;
PFNGLGENRENDERBUFFERSEXTPROC glGenRenderbuffersEXT = NULL;
PFNGLRENDERBUFFERSTORAGEEXTPROC glRenderbufferStorageEXT = NULL;
PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC glGetRenderbufferParameterivEXT = NULL;
PFNGLISFRAMEBUFFEREXTPROC glIsFramebufferEXT = NULL;
PFNGLBINDFRAMEBUFFEREXTPROC glBindFramebufferEXT = NULL;
PFNGLDELETEFRAMEBUFFERSEXTPROC glDeleteFramebuffersEXT = NULL;
PFNGLGENFRAMEBUFFERSEXTPROC glGenFramebuffersEXT = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC glCheckFramebufferStatusEXT = NULL;
PFNGLFRAMEBUFFERTEXTURE1DEXTPROC glFramebufferTexture1DEXT = NULL;
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC glFramebufferTexture2DEXT = NULL;
PFNGLFRAMEBUFFERTEXTURE3DEXTPROC glFramebufferTexture3DEXT = NULL;
PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC glFramebufferRenderbufferEXT = NULL;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC
		glGetFramebufferAttachmentParameterivEXT = NULL;
PFNGLGENERATEMIPMAPEXTPROC glGenerateMipmapEXT = NULL;
PFNGLCREATEPROGRAMOBJECTARBPROC glCreateProgramObjectARB = NULL;
PFNGLDELETEOBJECTARBPROC glDeleteObjectARB = NULL;
PFNGLUSEPROGRAMOBJECTARBPROC glUseProgramObjectARB = NULL;
PFNGLCREATESHADEROBJECTARBPROC glCreateShaderObjectARB = NULL;
PFNGLSHADERSOURCEARBPROC glShaderSourceARB = NULL;
PFNGLCOMPILESHADERARBPROC glCompileShaderARB = NULL;
PFNGLGETOBJECTPARAMETERIVARBPROC glGetObjectParameterivARB = NULL;
PFNGLATTACHOBJECTARBPROC glAttachObjectARB = NULL;
PFNGLGETINFOLOGARBPROC glGetInfoLogARB = NULL;
PFNGLLINKPROGRAMARBPROC glLinkProgramARB = NULL;
PFNGLGETUNIFORMLOCATIONARBPROC glGetUniformLocationARB = NULL;
PFNGLUNIFORM4FARBPROC glUniform4fARB = NULL;
PFNGLUNIFORM1IARBPROC glUniform1iARB = NULL;
PFNGLUNIFORM1FARBPROC glUniform1fARB = NULL;
PFNGLUNIFORMMATRIX4FVARBPROC glUniformMatrix4fvARB = NULL;
PFNGLBINDBUFFERARBPROC glBindBufferARB = NULL;
PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB = NULL;
PFNGLGENBUFFERSARBPROC glGenBuffersARB = NULL;
PFNGLBUFFERDATAARBPROC glBufferDataARB = NULL;
PFNGLMAPBUFFERARBPROC glMapBufferARB = NULL;
PFNGLUNMAPBUFFERARBPROC glUnmapBufferARB = NULL;
PFNGLVERTEXATTRIBPOINTERARBPROC glVertexAttribPointerARB = NULL;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC glEnableVertexAttribArrayARB = NULL;
PFNGLBINDATTRIBLOCATIONARBPROC glBindAttribLocationARB = NULL;
PFNGLGETATTRIBLOCATIONARBPROC glGetAttribLocationARB = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYARBPROC glDisableVertexAttribArrayARB;


int setupGLSL() {

	glIsRenderbufferEXT = (PFNGLISRENDERBUFFEREXTPROC) glfwGetProcAddress(
			"glIsRenderbufferEXT");
	glBindRenderbufferEXT = (PFNGLBINDRENDERBUFFEREXTPROC) glfwGetProcAddress(
			"glBindRenderbufferEXT");
	glDeleteRenderbuffersEXT
			= (PFNGLDELETERENDERBUFFERSEXTPROC) glfwGetProcAddress(
					"glDeleteRenderbuffersEXT");
	glGenRenderbuffersEXT = (PFNGLGENRENDERBUFFERSEXTPROC) glfwGetProcAddress(
			"glGenRenderbuffersEXT");
	glRenderbufferStorageEXT
			= (PFNGLRENDERBUFFERSTORAGEEXTPROC) glfwGetProcAddress(
					"glRenderbufferStorageEXT");
	glGetRenderbufferParameterivEXT
			= (PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC) glfwGetProcAddress(
					"glGetRenderbufferParameterivEXT");
	glIsFramebufferEXT = (PFNGLISFRAMEBUFFEREXTPROC) glfwGetProcAddress(
			"glIsFramebufferEXT");
	glBindFramebufferEXT = (PFNGLBINDFRAMEBUFFEREXTPROC) glfwGetProcAddress(
			"glBindFramebufferEXT");
	glDeleteFramebuffersEXT
			= (PFNGLDELETEFRAMEBUFFERSEXTPROC) glfwGetProcAddress(
					"glDeleteFramebuffersEXT");
	glGenFramebuffersEXT = (PFNGLGENFRAMEBUFFERSEXTPROC) glfwGetProcAddress(
			"glGenFramebuffersEXT");
	glCheckFramebufferStatusEXT
			= (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC) glfwGetProcAddress(
					"glCheckFramebufferStatusEXT");
	glFramebufferTexture1DEXT
			= (PFNGLFRAMEBUFFERTEXTURE1DEXTPROC) glfwGetProcAddress(
					"glFramebufferTexture1DEXT");
	glFramebufferTexture2DEXT
			= (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC) glfwGetProcAddress(
					"glFramebufferTexture2DEXT");
	glFramebufferTexture3DEXT
			= (PFNGLFRAMEBUFFERTEXTURE3DEXTPROC) glfwGetProcAddress(
					"glFramebufferTexture3DEXT");
	glFramebufferRenderbufferEXT
			= (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC) glfwGetProcAddress(
					"glFramebufferRenderbufferEXT");
	glGetFramebufferAttachmentParameterivEXT
			= (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC) glfwGetProcAddress(
					"glGetFramebufferAttachmentParameterivEXT");
	glGenerateMipmapEXT = (PFNGLGENERATEMIPMAPEXTPROC) glfwGetProcAddress(
			"glGenerateMipmapEXT");
	glCreateProgramObjectARB
			= (PFNGLCREATEPROGRAMOBJECTARBPROC) glfwGetProcAddress(
					"glCreateProgramObjectARB");
	glDeleteObjectARB = (PFNGLDELETEOBJECTARBPROC) glfwGetProcAddress(
			"glDeleteObjectARB");
	glUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC) glfwGetProcAddress(
			"glUseProgramObjectARB");
	glCreateShaderObjectARB
			= (PFNGLCREATESHADEROBJECTARBPROC) glfwGetProcAddress(
					"glCreateShaderObjectARB");
	glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC) glfwGetProcAddress(
			"glShaderSourceARB");
	glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC) glfwGetProcAddress(
			"glCompileShaderARB");
	glGetObjectParameterivARB
			= (PFNGLGETOBJECTPARAMETERIVARBPROC) glfwGetProcAddress(
					"glGetObjectParameterivARB");
	glAttachObjectARB = (PFNGLATTACHOBJECTARBPROC) glfwGetProcAddress(
			"glAttachObjectARB");
	glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC) glfwGetProcAddress(
			"glGetInfoLogARB");
	glLinkProgramARB = (PFNGLLINKPROGRAMARBPROC) glfwGetProcAddress(
			"glLinkProgramARB");
	glGetUniformLocationARB
			= (PFNGLGETUNIFORMLOCATIONARBPROC) glfwGetProcAddress(
					"glGetUniformLocationARB");
	glUniform4fARB = (PFNGLUNIFORM4FARBPROC) glfwGetProcAddress(
			"glUniform4fARB");
	glUniform1iARB = (PFNGLUNIFORM1IARBPROC) glfwGetProcAddress(
			"glUniform1iARB");
	glCreateProgramObjectARB
			= (PFNGLCREATEPROGRAMOBJECTARBPROC) glfwGetProcAddress(
					"glCreateProgramObjectARB");
	glDeleteObjectARB = (PFNGLDELETEOBJECTARBPROC) glfwGetProcAddress(
			"glDeleteObjectARB");
	glUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC) glfwGetProcAddress(
			"glUseProgramObjectARB");
	glCreateShaderObjectARB
			= (PFNGLCREATESHADEROBJECTARBPROC) glfwGetProcAddress(
					"glCreateShaderObjectARB");
	glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC) glfwGetProcAddress(
			"glShaderSourceARB");
	glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC) glfwGetProcAddress(
			"glCompileShaderARB");
	glGetObjectParameterivARB
			= (PFNGLGETOBJECTPARAMETERIVARBPROC) glfwGetProcAddress(
					"glGetObjectParameterivARB");
	glAttachObjectARB = (PFNGLATTACHOBJECTARBPROC) glfwGetProcAddress(
			"glAttachObjectARB");
	glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC) glfwGetProcAddress(
			"glGetInfoLogARB");
	glLinkProgramARB = (PFNGLLINKPROGRAMARBPROC) glfwGetProcAddress(
			"glLinkProgramARB");
	glGetUniformLocationARB
			= (PFNGLGETUNIFORMLOCATIONARBPROC) glfwGetProcAddress(
					"glGetUniformLocationARB");
	glUniform4fARB = (PFNGLUNIFORM4FARBPROC) glfwGetProcAddress(
			"glUniform4fARB");
	glUniform1iARB = (PFNGLUNIFORM1IARBPROC) glfwGetProcAddress(
			"glUniform1iARB");
	glUniform1fARB = (PFNGLUNIFORM1FARBPROC) glfwGetProcAddress(
			"glUniform1fARB");
	glUniformMatrix4fvARB =(PFNGLUNIFORMMATRIX4FVARBPROC) glfwGetProcAddress("glUniformMatrix4fvARB");
	glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) glfwGetProcAddress(
			"glGenBuffersARB");
	glBindBufferARB = (PFNGLBINDBUFFERARBPROC) glfwGetProcAddress(
			"glBindBufferARB");
	glBufferDataARB = (PFNGLBUFFERDATAARBPROC) glfwGetProcAddress(
			"glBufferDataARB");
	glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) glfwGetProcAddress(
			"glDeleteBuffersARB");
	glMapBufferARB = (PFNGLMAPBUFFERARBPROC) glfwGetProcAddress(
			"glMapBufferARB");
	glUnmapBufferARB = (PFNGLUNMAPBUFFERARBPROC) glfwGetProcAddress(
			"glUnmapBufferARB");
	glVertexAttribPointerARB
			= (PFNGLVERTEXATTRIBPOINTERARBPROC) glfwGetProcAddress(
					"glVertexAttribPointerARB");
	glEnableVertexAttribArrayARB
			= (PFNGLENABLEVERTEXATTRIBARRAYARBPROC) glfwGetProcAddress(
					"glEnableVertexAttribArrayARB");
	glBindAttribLocationARB
			= (PFNGLBINDATTRIBLOCATIONARBPROC) glfwGetProcAddress(
					"glBindAttribLocationARB");
	glGetAttribLocationARB
			= (PFNGLGETATTRIBLOCATIONARBPROC) glfwGetProcAddress(
					"glGetAttribLocationARB");
	glDisableVertexAttribArrayARB
			= (PFNGLDISABLEVERTEXATTRIBARRAYARBPROC) glfwGetProcAddress(
					" glDisableVertexAttribArrayARB");

}

bool checkFramebufferStatus() {
	// check FBO status
	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	switch (status) {
	case GL_FRAMEBUFFER_COMPLETE_EXT:
		std::cout << "Framebuffer complete." << std::endl;
		return true;

	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
		std::cout
				<< "[ERROR] Framebuffer incomplete: Attachment is NOT complete."
				<< std::endl;
		return false;

	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
		std::cout
				<< "[ERROR] Framebuffer incomplete: No image is attached to FBO."
				<< std::endl;
		return false;

	case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
		std::cout
				<< "[ERROR] Framebuffer incomplete: Attached images have different dimensions."
				<< std::endl;
		return false;

	case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
		std::cout
				<< "[ERROR] Framebuffer incomplete: Color attached images have different internal formats."
				<< std::endl;
		return false;

	case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
		std::cout << "[ERROR] Framebuffer incomplete: Draw buffer."
				<< std::endl;
		return false;

	case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
		std::cout << "[ERROR] Framebuffer incomplete: Read buffer."
				<< std::endl;
		return false;

	case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
		std::cout << "[ERROR] Unsupported by FBO implementation." << std::endl;
		return false;

	default:
		std::cout << "[ERROR] Unknow error." << std::endl;
		return false;
	}
}
