# Contributing to Discord Bot Manager

First of all, thank you for considering contributing to the Discord Bot Manager! We welcome all contributions, whether you're fixing a bug, adding new features, or improving documentation. This guide will help you get started and ensure that your contributions align with the project's standards.

## Prerequisites

Before you begin, ensure you have the following installed:
- Windows 10 or newer
- vcpkg package manager
- D++ (DPP) library

## How Can I Contribute?

### 1. Reporting Bugs

If you encounter any issues or bugs while using Discord Bot Manager, we encourage you to report them. Please follow these steps:

1. **Search for existing issues**: Before submitting a new bug report, check the issues to see if the bug has already been reported.
2. **Create a new issue**: If no one has reported the issue, submit a bug report following the template below:
   - Title: Briefly describe the issue
   - Description: Provide detailed steps to reproduce the issue
   - Expected behavior: Explain what you expected to happen
   - Actual behavior: Describe what actually happened
   - Environment: Include OS version, Discord Bot Manager version, and any other relevant details

**Tip**: You can use the following format for reporting issues:
```
**Your Name**:
**Issue**:
**How it happened**:
```

### 2. Suggesting Features

We value your ideas! If you have suggestions to enhance the project, follow this process:

1. **Search for similar feature requests**: Before creating a new request, review existing issues and feature requests.
2. **Submit your suggestion**: If your idea is unique, create a new issue labeled "enhancement" and clearly describe:
   - Feature: What is the new functionality you're suggesting?
   - Use case: Why is this feature valuable?
   - Alternatives: Are there any other ways to achieve the same result?

### 3. Submitting Pull Requests (PRs)

If you're ready to contribute code, follow these steps:

#### Step 1: Fork the Repository
1. Go to the Discord Bot Manager GitHub page
2. Click the "Fork" button in the top-right corner to create a copy of the repository in your GitHub account

#### Step 2: Set Up Your Development Environment
1. Clone your fork:
```bash
git clone https://github.com/Jadeeeeeeeeeeee/discordbotmanager.git
cd discordbotmanager
```

2. Create a new branch:
```bash
git checkout -b your-branch-name
```

#### Step 3: Make Your Changes
- Follow coding best practices and keep changes focused on one feature or fix
- Make sure the project builds and runs successfully after your changes

#### Step 4: Commit Your Changes
Write clear commit messages: Each commit should explain the reason for the change.
```bash
git add .
git commit -m "Your descriptive commit message"
```

#### Step 5: Push Your Changes
Push the branch to your GitHub repository:
```bash
git push origin your-branch-name
```

#### Step 6: Create a Pull Request
1. Go to your fork on GitHub
2. Click the "Compare & pull request" button
3. Provide a detailed description of your changes and reference any related issues

### 4. Code Style Guidelines

To maintain consistency across the project, please follow these guidelines:

- Use clear and descriptive variable and function names
- Comment your code where necessary, especially in complex sections
- Follow the existing code style and structure used in the project
- Ensure your code is free from syntax errors and passes any pre-existing tests

### 5. Improving Documentation

If you notice any gaps or inaccuracies in the documentation, feel free to submit updates. This can be done by:

- Modifying or adding sections in the README or other documentation files
- Fixing typos or clarifying confusing statements

## How to Set Up the Project Locally

1. Fork and clone the repo (see step 2 above)
2. Ensure you have the correct dependencies:
   - Windows 10 or newer
   - Install vcpkg package manager
   - Install D++ (DPP) library through vcpkg
   - This project is designed for Windows only, and Linux/macOS versions are not supported
3. Run the application:
   - Use the command prompt to execute discordbot.exe and start working on the project

## Code of Conduct

By participating in this project, you agree to uphold our Code of Conduct. This ensures a welcoming environment for all contributors.
