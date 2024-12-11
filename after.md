
// in header
CMD_States vgit_commit(const std::string &message);
CMD_States vgit_status(const std::string &message);
CMD_States vgit_log(const std::string &message);
CMD_States vgit_branch(const std::string &message);
CMD_States vgit_checkout(const std::string &message);
CMD_States vgit_merge(const std::string &message);
CMD_States vgit_push(const std::string &message);
CMD_States vgit_pull(const std::string &message);
CMD_States vgit_clone(const std::string &message);
CMD_States vgit_version(const std::string &message);
CMD_States vgit_config(const std::string &message);
CMD_States vgit_remote(const std::string &message);
CMD_States vgit_tag(const std::string &message);
CMD_States vgit_fetch(const std::string &message);
CMD_States vgit_help(const std::string &message);


// in constructor
command_map["vgit commit"] = [this](const std::string& arg) { return vgit_commit(arg); };
command_map["vgit status"] = [this](const std::string& arg) { return vgit_status(arg); };
command_map["vgit branch"] = [this](const std::string& arg) { return vgit_branch(arg); };
command_map["vgit checkout"] = [this](const std::string& arg) { return vgit_checkout(arg); };
command_map["vgit merge"] = [this](const std::string& arg) { return vgit_merge(arg); };
command_map["vgit push"] = [this](const std::string& arg) { return vgit_push(arg); };
command_map["vgit pull"] = [this](const std::string& arg) { return vgit_pull(arg); };
command_map["vgit clone"] = [this](const std::string& arg) { return vgit_clone(arg); };
command_map["vgit help"] = [this](const std::string& arg) { return vgit_help(arg); };
command_map["vgit version"] = [this](const std::string& arg) { return vgit_version(arg); };
command_map["vgit config"] = [this](const std::string& arg) { return vgit_config(arg); };
command_map["vgit remote"] = [this](const std::string& arg) { return vgit_remote(arg); };
command_map["vgit tag"] = [this](const std::string& arg) { return vgit_tag(arg); };
command_map["vgit fetch"] = [this](const std::string& arg) { return vgit_fetch(arg); };



// in cpp file
vgit::CMD_States vgit::vgit_commit(const std::string &message){

    return CMD_States::Success;
}


vgit::CMD_States vgit::vgit_status(const std::string &message){

    return CMD_States::Success;
}


vgit::CMD_States vgit::vgit_log(const std::string &message){

    return CMD_States::Success;
}


vgit::CMD_States vgit::vgit_branch(const std::string &message){

    return CMD_States::Success;
}


vgit::CMD_States vgit::vgit_checkout(const std::string &message){

    return CMD_States::Success;
}


vgit::CMD_States vgit::vgit_merge(const std::string &message){

    return CMD_States::Success;
}


vgit::CMD_States vgit::vgit_push(const std::string &message){

    return CMD_States::Success;
}


vgit::CMD_States vgit::vgit_pull(const std::string &message){

    return CMD_States::Success;
}


vgit::CMD_States vgit::vgit_clone(const std::string &message){

    return CMD_States::Success;
}

vgit::CMD_States vgit::vgit_version(const std::string &message){
    return CMD_States::Success;
}


vgit::CMD_States vgit::vgit_config(const std::string &message){
    return CMD_States::Success;
}


vgit::CMD_States vgit::vgit_remote(const std::string &message){
    return CMD_States::Success;
}


vgit::CMD_States vgit::vgit_tag(const std::string &message){
    return CMD_States::Success;
}


vgit::CMD_States vgit::vgit_fetch(const std::string &message){
    return CMD_States::Success;
}


vgit::CMD_States vgit::vgit_help(const std::string &message){
    
    return CMD_States::Success;
}