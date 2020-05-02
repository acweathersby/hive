#pragma once


#include "./pipeline.hpp"
namespace hive
{

    namespace gl
    {
        SmartGLPipeline createPipeline(std::vector<Program> programs)
        {
            unsigned pipeline;

            SmartGLPipeline smpipeline;

            glGenProgramPipelines(1, &pipeline);

            uint stage_bits = 0;

            if (pipeline > 0) {
                for (auto program : programs) {
                    if (program.IS_USABLE() && program.PIPELINEABLE()) {
                        uint program_stages = 0;
                        if (program.HAVE_COMP()) program_stages |= GL_COMPUTE_SHADER_BIT;
                        if (program.HAVE_FRAG()) program_stages |= GL_FRAGMENT_SHADER_BIT;
                        if (program.HAVE_EVAL()) program_stages |= GL_TESS_EVALUATION_SHADER_BIT;
                        if (program.HAVE_VERT()) program_stages |= GL_VERTEX_SHADER_BIT;
                        if (program.HAVE_GEOM()) program_stages |= GL_GEOMETRY_SHADER_BIT;
                        if (program.HAVE_TESS()) program_stages |= GL_TESS_CONTROL_SHADER_BIT;

                        if (program_stages & stage_bits) {
                            // TODO Some type of overlap error, or warning?
                        }

                        glUseProgramStages(pipeline, program_stages, program.gli());

                        stage_bits |= program_stages;
                    }
                }

                smpipeline = SmartGLPipeline(pipeline, true, programs);
            }

            return smpipeline;
        }

        bool SmartGLPipeline::IS_USABLE() { return IS_READY && pointer > -1; }

        void SmartGLPipeline::use()
        {
            if (!IS_READY) {
                // SKCH_ERROR("Attempt to use gl program that is not ready to be used.");
            } else if (bound_program != pointer) {
                glUseProgram(pointer);
                // glBindVertexArray(vertex_array_object);
                bound_program = pointer;
            }
        }

        void SmartGLPipeline::release()
        {
            if (pointer < 0) return;
            bound_program = -1;
            glUseProgram(0);
            glBindVertexArray(0);
        }

        void SmartGLPipeline::deleteUnderlyingGLResource()
        {
            if (pointer > -1) {
                // glDeleteVertexArrays(1, &vertex_array_object);
                const unsigned pipe = pointer;
                glDeleteProgramPipelines(1, &pipe);
            }
            IS_READY = false;
        }
    } // namespace gl
} // namespace hive