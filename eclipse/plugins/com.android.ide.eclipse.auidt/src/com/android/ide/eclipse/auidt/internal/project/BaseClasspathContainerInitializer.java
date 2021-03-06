/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Eclipse Public License, Version 1.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.eclipse.org/org/documents/epl-v10.php
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.android.ide.eclipse.auidt.internal.project;

import com.android.ide.eclipse.auidt.AdtPlugin;

import org.eclipse.core.resources.IMarker;
import org.eclipse.core.resources.IProject;
import org.eclipse.core.resources.IResource;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.core.runtime.IStatus;
import org.eclipse.core.runtime.Status;
import org.eclipse.core.runtime.jobs.Job;
import org.eclipse.jdt.core.ClasspathContainerInitializer;

/**
 * Base CPC initializer providing support to all our initializer.
 *
 */
abstract class BaseClasspathContainerInitializer extends ClasspathContainerInitializer {


    /**
     * Adds an error to a project, or remove all markers if error message is null
     * @param project the project to modify
     * @param errorMessage the errorMessage or null to remove errors.
     * @param markerType the marker type to be used.
     * @param outputToConsole whether to output to the console.
     */
    protected static void processError(final IProject project, final String errorMessage,
            final String markerType, boolean outputToConsole) {
        if (errorMessage != null) {
            // log the error and put the marker on the project if we can.
            if (outputToConsole) {
                AdtPlugin.printErrorToConsole(project, errorMessage);
            }

            try {
                BaseProjectHelper.markProject(project, markerType,
                        errorMessage, IMarker.SEVERITY_ERROR, IMarker.PRIORITY_HIGH);
            } catch (CoreException e) {
                // In some cases, the workspace may be locked for modification when we
                // pass here.
                // We schedule a new job to put the marker after.
                final String fmessage = errorMessage;
                Job markerJob = new Job("Android SDK: Resolving error markers") {
                    @Override
                    protected IStatus run(IProgressMonitor monitor) {
                        try {
                            BaseProjectHelper.markProject(project,
                                    markerType,
                                    fmessage, IMarker.SEVERITY_ERROR,
                                    IMarker.PRIORITY_HIGH);
                        } catch (CoreException e2) {
                            return e2.getStatus();
                        }

                        return Status.OK_STATUS;
                    }
                };

                // build jobs are run after other interactive jobs
                markerJob.setPriority(Job.BUILD);
                markerJob.schedule();
            }
        } else {
            // no error, remove existing markers.
            try {
                if (project.exists()) {
                    project.deleteMarkers(markerType, true,
                            IResource.DEPTH_INFINITE);
                }
            } catch (CoreException ce) {
                // In some cases, the workspace may be locked for modification when we pass
                // here, so we schedule a new job to put the marker after.
                Job markerJob = new Job("Android SDK: Resolving error markers") {
                    @Override
                    protected IStatus run(IProgressMonitor monitor) {
                        try {
                            project.deleteMarkers(markerType, true,
                                    IResource.DEPTH_INFINITE);
                        } catch (CoreException e2) {
                            return e2.getStatus();
                        }

                        return Status.OK_STATUS;
                    }
                };

                // build jobs are run after other interactive jobs
                markerJob.setPriority(Job.BUILD);
                markerJob.schedule();
            }
        }
    }
}
