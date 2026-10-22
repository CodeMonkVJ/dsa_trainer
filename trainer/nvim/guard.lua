local attempt = vim.env.DSA_ATTEMPT_FILE
if not attempt or attempt == "" then
  error("DSA_ATTEMPT_FILE is required")
end

local function normalize(path)
  local real = vim.uv.fs_realpath(path)
  return real or vim.fs.normalize(path)
end

attempt = normalize(attempt)

local function protect_buffer(buffer)
  if not vim.api.nvim_buf_is_valid(buffer) then return end
  if vim.bo[buffer].buftype == "terminal" then
    local job = vim.b[buffer].terminal_job_id
    if job then pcall(vim.fn.jobstop, job) end
    vim.schedule(function()
      if vim.api.nvim_buf_is_valid(buffer) then
        pcall(vim.api.nvim_buf_delete, buffer, { force = true })
        vim.notify("Terminal buffers are disabled in Interview Trainer practice sessions", vim.log.levels.ERROR)
      end
    end)
    return
  end
  if vim.bo[buffer].buftype ~= "" then return end
  local name = vim.api.nvim_buf_get_name(buffer)
  if name == "" or normalize(name) == attempt then return end
  vim.bo[buffer].modifiable = false
  vim.bo[buffer].readonly = true
end

vim.api.nvim_create_autocmd({ "BufEnter", "BufReadPost", "BufNewFile", "TermOpen" }, {
  callback = function(event) protect_buffer(event.buf) end,
  desc = "Restrict Interview Trainer practice to the active attempt file",
})

vim.api.nvim_create_autocmd("BufWritePre", {
  callback = function(event)
    if normalize(vim.api.nvim_buf_get_name(event.buf)) ~= attempt then
      error("Interview Trainer practice may only write the active attempt file")
    end
  end,
  desc = "Prevent writes outside the active DSA attempt",
})

for _, buffer in ipairs(vim.api.nvim_list_bufs()) do
  protect_buffer(buffer)
end
